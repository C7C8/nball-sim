#include "../lib/Hydra.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
using namespace std;
using namespace Hydra;

//Macros
#define OUTPUT_COORDS(a, b) "(" << a << ", " << b << ")"
#define SIZEMASS_RATIO(m) 1.1 * sqrt(m)

//Constants
#define GRAV_CONST 1000.0
#define JUMP_CONST 0.025
#define THROW_CONST 2.0
#define MAX_MASS 500
#define FPS 60.0
#define TIMESTEP (1000.0 / FPS)
#define PHYSTEP .016
#define ICOLLISIONS
//#define ECOLLISIONS
//#define AIR_RESISTANCE 0.001
//#define DIST_CHECK
#define COMSIZE 4.0
#define TRAILLENGTH 200
#define NUMRAND 15
#define RANDINITVEL 40.0
#define RANDINITMASS 160.0

//Functions
Vector2D forcev(struct nball m1, struct nball m2);

struct nball
{
	nball(Texture newSprite, double newPX, double newPY, double newMass = 50.0);
	inline void render(HydraEngine* engine);
	Texture sprite;
	double posX;
	double posY;
	Vector2D vel;
	Vector2D forces;
	double mass;
	float size;
	vector<SDL_Point> trail;
};

int main(int argc, char* argv[])
{
	srand(time(0));
	HydraEngine* engine = HydraEngine::getInstance();
	engine->init();
	engine->setWSize(1300, 680);
	engine->setWTitle("N-Body Simulator");
	TextureManager* tManage = TextureManager::getInstance();
	tManage->loadTexture("Ball2.png", "ball");
	Texture sprite = tManage->getTexture("ball");

	SDL_Rect screenRect;
	screenRect.x = 0; screenRect.y = 0;
	screenRect.w = engine->getWXSize(); screenRect.h = engine->getWYSize();
	SDL_SetRenderDrawColor(engine->getRenderer(), 255, 255, 255, 100);

	vector<nball> balls;

	Timer fpstimer;
	bool quit = false;
	bool edges = false;
	bool centmass = true;
	bool trails = true;
	bool persTrails = false; //Persistent trails
	nball tempBall(sprite, 0, 0, 160);
	bool placing = false;

	//Logging stuff
	int frame = 0;
	system("rm log.csv"); //Whoops! How did THIS get here?
	ofstream log;
	log.open("log.csv");
	log << "Frame, Kinetic, Potential, Total" << endl;

	while (!quit)
	{
		frame++;
		fpstimer.start();
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.button.type == SDL_MOUSEBUTTONDOWN)
			{ //Start placing a ball
				if (!placing)
				{
					tempBall.posX = event.button.x;
					tempBall.posY = event.button.y;
				}
				placing = true;
			}
			else if (event.button.type == SDL_MOUSEBUTTONUP && placing)
			{ //Add a ball in the process of being placed
				Vector2D newVel(tempBall.posX - event.button.x, tempBall.posY - event.button.y);
				tempBall.vel = newVel * THROW_CONST;
				balls.push_back(tempBall);
				placing = false;
			}
			else if (event.key.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_c)
					balls.clear();
				else if (event.key.keysym.sym == SDLK_f)
					engine->setFullscreen(!engine->getFullscreen());
				else if (event.key.keysym.sym == SDLK_s)
					for (auto iter = balls.begin(); iter != balls.end(); iter++)
						iter->vel.setMag(0);
				else if (event.key.keysym.sym == SDLK_e)
				{
					edges = !edges;
					if (edges)
					{ //Move all balls back onto the screen when edges are disabled.
						for (auto iter = balls.begin(); iter != balls.end(); iter++)
						{
							if (iter->posX < iter->size / 2.0)
								iter->posX = iter->size / 2.0;
							if (iter->posX > engine->getWXSize() - (iter->size / 2))
								iter->posX = engine->getWXSize() - (iter->size / 2);
							if (iter->posY < iter->size / 2.0)
								iter->posY = iter->size / 2.0;
							if (iter->posY > engine->getWYSize() - (iter->size / 2))
								iter->posY = engine->getWYSize() - (iter->size / 2);
						}
					}
				}
				else if (event.key.keysym.sym == SDLK_w && placing)
				{
					tempBall.mass += 20;
					tempBall.size = SIZEMASS_RATIO(tempBall.mass);
				}
				else if (event.key.keysym.sym == SDLK_q && placing && tempBall.mass > 2)
				{
					tempBall.mass -= 20;
					tempBall.size = SIZEMASS_RATIO(tempBall.mass);
				}
				else if (event.key.keysym.sym == SDLK_r)
				{
					tempBall.mass = (rand() % MAX_MASS) + 1;
					tempBall.size = SIZEMASS_RATIO(tempBall.mass);
				}
				else if (event.key.keysym.sym == SDLK_z)
				{
					centmass = !centmass;
				}
				else if (event.key.keysym.sym == SDLK_1)
				{
					nball nm1(sprite, 200, 200, 300), nm2(sprite, 250, 250, 300);
					nm1.vel.setY(25);
					nm2.vel.setY(-25);
					nm1.vel.setX(0); //Not sure if these x vel sets are needed, but whatever.
					nm2.vel.setX(0);
					balls.push_back(nm1);
					balls.push_back(nm2);
				}
				else if (event.key.keysym.sym == SDLK_t)
				{
					trails = !trails;
					if (!trails)
					{
						for (auto iter = balls.begin(); iter!= balls.end(); iter++)
							iter->trail.clear();
					}
				}
				else if (event.key.keysym.sym == SDLK_p)
				{
					persTrails = !persTrails;
					if (!persTrails)
					{
						for (auto iter = balls.begin(); iter != balls.end(); iter++)
						{
							while (iter->trail.size() > TRAILLENGTH)
								iter->trail.pop_back();
						}
					}
				}
				else if (event.key.keysym.sym == SDLK_o)
				{
					for (int i = 0; i < NUMRAND; i++)
					{
						nball newBall(sprite, rand() % engine->getWXSize(), rand() % engine->getWYSize(), RANDINITMASS);
						newBall.vel.setX(1);
						newBall.vel.setY(0);
						newBall.vel.setMag(RANDINITVEL);
						newBall.vel.rotate(Angle::toRads(rand() % 360));
						balls.push_back(newBall);
					}
				}
			}
		}

		//Reset accels
		for (auto iter = balls.begin(); iter != balls.end(); iter++)
		{
			iter->forces.setX(0);
			iter->forces.setY(0);
		}

		//Add current positions to trail list
		for (auto iter = balls.begin(); iter != balls.end(); iter++)
		{
			SDL_Point pos;
			pos.x = iter->posX;
			pos.y = iter->posY;
			iter->trail.insert(iter->trail.begin(), pos); //Add to beginning
			if (iter->trail.size() > TRAILLENGTH && !persTrails)
				iter->trail.pop_back(); //Remove end
		}

		//Calculate forces
		for (auto m1 = balls.begin(); m1 != balls.end(); m1++)
		{
			for (auto m2 = balls.begin(); m2 != balls.end(); m2++)
			{
				if (m1 == m2)
					continue;
				m1->forces = m1->forces + forcev(*m1, *m2);
			}
		}

		//Positions, half-update velocities
		for (auto ball = balls.begin(); ball != balls.end(); ball++)
		{
			ball->posX += ball->vel.getX() * PHYSTEP + 0.5*(ball->forces.getX() / ball->mass) * PHYSTEP * PHYSTEP;
			ball->posY += ball->vel.getY() * PHYSTEP + 0.5*(ball->forces.getY() / ball->mass) * PHYSTEP * PHYSTEP;
			ball->vel.setX(ball->vel.getX() + (0.5 * (ball->forces.getX() / ball->mass) * PHYSTEP));
			ball->vel.setY(ball->vel.getY() + (0.5 * (ball->forces.getY() / ball->mass) * PHYSTEP));
		}

		//Reset accels
		for (auto iter = balls.begin(); iter != balls.end(); iter++)
		{
			iter->forces.setX(0);
			iter->forces.setY(0);
		}

		//Calculate forces
		for (auto m1 = balls.begin(); m1 != balls.end(); m1++)
		{
			for (auto m2 = balls.begin(); m2 != balls.end(); m2++)
			{
				if (m1 == m2)
					continue;
				m1->forces = m1->forces + forcev(*m1, *m2);
			}
		}

		//Second half-update velocities
		for (auto ball = balls.begin(); ball != balls.end(); ball++)
		{
			ball->vel.setX(ball->vel.getX() + (0.5 * (ball->forces.getX() / ball->mass) * PHYSTEP));
			ball->vel.setY(ball->vel.getY() + (0.5 * (ball->forces.getY() / ball->mass) * PHYSTEP));
		}

		//Collisions
#ifdef COLLISIONS
		//Elastitc collisions
#ifdef ECOLLISIONS
		for (auto m1 = balls.begin(); m1 != balls.end(); m1++)
		{
			for (auto m2 = balls.begin(); m2 != balls.end(); m2++)
			{
				if (m2 == m1)
					continue; //skip self

				Vector2D distance(m2->posX - m1->posX, m2->posY - m1->posY);
				if (distance.getMag() <= (m1->size + m2->size) / 2.f)
				{
					Vector2D unitNormal(m2->posX - m1->posX, m2->posY - m1->posY);
					unitNormal.normalize();
					Vector2D unitTangent(-unitNormal.getY(), unitNormal.getX());
					//Step 2 skipped, I already have the velocity vectors
					//Step 3
					double v1n = unitNormal * m1->vel;
					double v1t = unitTangent * m1->vel;
					double v2n = unitNormal * m2->vel;
					double v2t = unitTangent * m2->vel;
					//Step 4
					double vP1t = v1t;
					double vP2t = v2t;
					//Step 5
					double vP1n = (v1n * (m1->mass - m2->mass) + (2 * m2->mass * v2n)) / (m1->mass + m2->mass);
					double vP2n = (v2n * (m2->mass - m1->mass) + (2 * m1->mass * v1n)) / (m1->mass + m2->mass);
					//Step 6
					Vector2D vvP1n = unitNormal * vP1n;
					Vector2D vvP1t = unitTangent * vP1t;
					Vector2D vvP2n = unitNormal * vP2n;
					Vector2D vvP2t = unitTangent * vP2t;
					//Step 7
					m1->vel = vvP1n + vvP1t;
					m2->vel = vvP2n + vvP2t;
					m1->posX += m1->vel.getX() * JUMP_CONST; m1->posY += m1->vel.getY() * JUMP_CONST;
					m2->posX += m2->vel.getX() * JUMP_CONST; m2->posY += m2->vel.getY() * JUMP_CONST;
				}
			}
		}
#endif

#ifdef ICOLLISIONS
		for (auto m1 = balls.begin(); m1 != balls.end(); m1++)
		{
			for (auto m2 = balls.begin(); m2 != balls.end(); m2++)
			{
				if (m2 == m1)
					continue; //skip self

				Vector2D distance(m2->posX - m1->posX, m2->posY - m1->posY);
				if (distance.getMag() >= (m1->size + m2->size) / 2.f)
					continue; //Ignore non-colliding objects

				nball newBall(sprite, 0, 0);
				newBall.mass = m1->mass + m2->mass;
				newBall.size = SIZEMASS_RATIO(newBall.mass);
				newBall.vel.setX(((m1->mass * m1->vel.getX()) + (m2->mass * m2->vel.getX())) / newBall.mass);
				newBall.vel.setY(((m1->mass * m1->vel.getY()) + (m2->mass * m2->vel.getY())) / newBall.mass);

				//Compute center of mass
				newBall.posX = ((m1->mass * m1->posX) + (m2->mass * m2->posX)) / newBall.mass;
				newBall.posY = ((m1->mass * m1->posY) + (m2->mass * m2->posY)) / newBall.mass;

				m1 = balls.erase(m1) - 1; //Returns value AFTER
				m2 = balls.erase(m2) - 1;
				balls.push_back(newBall);
			}
		}
#endif

		//Edge collisions
		for (auto iter = balls.begin(); iter != balls.end(); iter++)
		{
			//Edge collisions
			if (edges)
			{
				if (iter->posX >  engine->getWXSize() - (iter->size / 2.0) || iter->posX < (iter->size / 2.0))
				{
					iter->vel.setX(-iter->vel.getX());
					iter->posX > (iter->size / 2.0) ? iter->posX = engine->getWXSize() - (iter->size / 2.0) : iter->posX = iter->size / 2.0;
				}
				if (iter->posY > engine->getWYSize() - (iter->size / 2.0) || iter->posY < (iter->size / 2.0))
				{
					iter->vel.setY(-iter->vel.getY());
					iter->posY > (iter->size / 2.0) ? iter->posY = engine->getWYSize() - (iter->size / 2.0) : iter->posY = iter->size / 2.0;
				}
			}
		}

		while (!fpstimer.hasIntervalPassed(TIMESTEP));
		SDL_SetRenderDrawColor(engine->getRenderer(), 255, 255, 255, 100);
		SDL_RenderFillRect(engine->getRenderer(), &screenRect);

		//Render everything!
		for (auto iter = balls.begin(); iter != balls.end(); iter++)
			iter->render(engine);

		//Trails
		if (trails)
		{
			SDL_SetRenderDrawColor(engine->getRenderer(), 0, 0, 0, 0); //Black
			for (auto iter = balls.begin(); iter != balls.end(); iter++)
			{
				for (auto point = iter->trail.begin(); point != iter->trail.end(); point++)
				{
					if (point == iter->trail.begin())
					{
						SDL_RenderDrawLine(engine->getRenderer(), iter->posX, iter->posY, point->x, point->y);
						continue;
					}
					auto lastPoint = point - 1;
					SDL_RenderDrawLine(engine->getRenderer(), lastPoint->x, lastPoint->y, point->x, point->y);
				}
			}
		}

		//Center of mass
		if (centmass)
		{
			double m = 0, mx = 0, my = 0;
			for (auto ball = balls.begin(); ball != balls.end(); ball++)
			{
				mx += ball->posX * ball->mass;
				my += ball->posY * ball->mass;
				m += ball->mass;
			}
			mx /= m;
			my /= m;
			SDL_Rect com;
			com.h = com.w = COMSIZE;
			com.x = mx - (COMSIZE / 2);
			com.y = my - (COMSIZE / 2);
			SDL_SetRenderDrawColor(engine->getRenderer(), 255, 0, 0, 255);
			SDL_RenderFillRect(engine->getRenderer(), &com);
		}

		if (placing)
		{
			tempBall.render(engine);
			int mX, mY;
			SDL_GetMouseState(&mX, &mY);
			SDL_SetRenderDrawColor(engine->getRenderer(), 0, 0, 0, 0);
			SDL_RenderDrawLine(engine->getRenderer(), tempBall.posX, tempBall.posY,
					tempBall.posX + (tempBall.posX - mX), tempBall.posY + (tempBall.posY - mY));
			SDL_SetRenderDrawColor(engine->getRenderer(), 255, 255, 255, 100);
		}

//		//Calculate energy for debugging purposes
		double Ek = 0;
		for (auto iter = balls.begin(); iter != balls.end(); iter++)
			Ek += iter->mass * pow(iter->vel.getMag(), 2.0) * 0.5;
		//cout << "Kinetic Energy: " << Ek << " J.\t";

		//Calculate total potential energy for debugging purposes
		//http://physics.stackexchange.com/questions/146108/is-there-anything-interesting-about-an-n-body-system-whose-potential-energy-is-c
		double Ep = 0;
		for (auto m1 = balls.begin(); m1 != balls.end(); m1++)
		{
			for (auto m2 = balls.begin(); m2 != balls.end(); m2++)
			{
				if (m1 == m2)
					continue; //Skip self
				Vector2D dist(m2->posX - m1->posX, m2->posY - m1->posY);
				Ep += (GRAV_CONST * m1->mass * m2->mass) / dist.getMag();
			}
		}
		Ep *= -0.5;
		//cout << "GP Energy: " << Ep << "\tJ. Total: " << Ek + Ep << "J." <<endl;
		//log << frame << ", " << Ek << "," << Ep << "," << Ek + Ep << endl;

		engine->renderAll();
	}

	log.close();
	tManage->freeAll();
	engine->shutdown();
	return 0;
}

nball::nball(Texture newSprite, double newPX, double newPY, double newMass)
{
	sprite = newSprite;
	posX = newPX;
	posY = newPY;
	mass = newMass;
	size = SIZEMASS_RATIO(mass);
}
void nball::render(HydraEngine* engine)
{
	sprite.setX(posX - (size / 2.f));
	sprite.setY(posY - (size / 2.f));
	sprite.setL(25.0 / mass);
	sprite.setScaleW(size);
	sprite.setScaleH(size);
	sprite.setL(MAX_MASS / mass);
	engine->queueTexture(sprite);
}

Vector2D forcev(nball m1, nball m2)
{
	//TODO: Force dampening
	//http://physics.stackexchange.com/questions/120183/why-does-my-gravity-simulation-do-this
	Vector2D force;
	force.setX(m1.posX - m2.posX);
	force.setY(m1.posY - m2.posY);
#ifdef DIST_CHECK
	if (force.getMag() < (m1.size + m2.size) / 2.0)
	{
		force.setX(0);
		force.setY(0);
		return force;
	}
#endif

	force.setMag((GRAV_CONST * -m1.mass * m2.mass) / (force.getMag() * force.getMag())); //Gravity formula for acceleration
	return force;
}
