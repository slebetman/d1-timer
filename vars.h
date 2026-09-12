#include <EEPROM.h>

extern struct Vars vars;

#ifndef VARS_H
#define VARS_H

const uint32_t MAGIC = 0xabcdef00;

struct Vars
{
	uint32_t magic;
	byte max;
	float rampUp;
	float cruise;
	float rampDown;
};

Vars vars;

void initVars()
{
	EEPROM.begin(sizeof(vars));
}

void saveVars()
{
	EEPROM.put(0, vars);
	EEPROM.commit();
}

Vars *readVars()
{
	EEPROM.get(0, vars);

	if (vars.magic != MAGIC)
	{
		// defaults:
		vars.magic = MAGIC;
		vars.max = 255;
		vars.rampUp = 0.5;
		vars.cruise = 10;
		vars.rampDown = 1.5;

		saveVars();
	}

	return &vars;
}

#endif