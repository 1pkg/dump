#ifndef __RESOURCES_CONTSANTS_HPP__
#define __RESOURCES_CONTSANTS_HPP__

namespace Resources
{

namespace Constants
{

/*			PhysicsMask			*/
static const int CHARACTER_MASK = 0x1;

static const int LINE_MASK = 0x2;

static const int SPIKES_MASK = 0x4;
static const int EDGE_MASK = 0x8;

static const int SHELL_MASK = 0x16;

static const int CASTER_MASK = 0x32;
			/**/

/*			PARTICLE			*/
static const int DEFAULT_PARTICLE_MAX_COUNT = 200;

static const float DEFAULT_PARTICLE_LIFE_TIME = 1.0f;

static const float DEFAULT_PARTICLE_EMISSION_RATE = 100.0f;

static const float DEFAULT_PARTICLE_SIZE_SCALE = 0.02f;

static const float DEFAULT_PARTICLE_GRAVITY_SCALE = 0.05f;
			/**/

/*			SPIKES			*/
static const float SPIKES_MAX_WIDTH_SCALE = 0.07f;
static const float SPIKES_MIN_WIDTH_SCALE = 0.01f;

static const float SPIKES_MAX_HEIGT_SCALE = 0.2f;
static const float SPIKES_MIN_HEIGT_SCALE = 0.15f;
			/**/

/*			EDGE			*/
static const float EDGE_WIDTH_SCALE = 0.1f;
			/**/

static const float SCORE_DIVIDED_KOEFICIENT = 1000.0f;

static const float GENERATOR_UPDATE_TIME = 3.0f;

static const int GENERATOR_DEFAULT_BYPASSING = 3;

static const float OBJECT_REALESE_TIME = 10.0f;

static const float LINE_REALESE_TIME = 5.0f;

static const float DRAW_LINE_WIDTH = 1.0f;

static const float LINE_MIN_LENTH = 15.0f;

static const float DYE_MIN_AMOUNT = 15.0f;

static const float DEFAULT_DYE_AMOUNT = 1500.0f;

static const float FRAME_RATE = 1.0f / 90.0f;

static const float SCENE_SPEED = 1.0f;

static const float SCENE_HEIGHT_SCALE = 10.0f;

static const float SCENE_OBJECT_DYING_POSITION_SCALE = -0.5f;

}

}

#endif