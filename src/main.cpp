#include "Headers/Classes/Game.h"

#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui-SFML_export.h>

int main (int argc, char* argv[]) {
	Game game;

	while (game.running()) {
		game.update();
		game.render();
	}
	
	return 0;
}
