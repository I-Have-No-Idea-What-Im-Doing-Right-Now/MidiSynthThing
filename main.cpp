#include <iostream>
#include <vector>
#include "utils.h"
#include "Synth.h"

int main() {
	Synth x;
	x.GenerateFile(5, 0.8, 440, "file.wav", false);
}