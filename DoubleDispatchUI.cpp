/* 
Test code on double dispatch design pattern in a dynamic way, during runtime.
Used to render a board game serie in cli or gui mode.
Note that C++ cannot directly support double dispatch.

by Tassos 2022
*/

#include <iostream>

int main() {
	struct Renderer;	// forward declaration

	struct GameBase {	// pure abstruct game base class 
	public:
		virtual void renderOn(const Renderer& renderer) const = 0;
	};

	// forward declarations of game types
	struct GameTypeA;
	struct GameTypeB;

	struct Renderer { // pure abstruct base class of renderers of games
		virtual void render(const GameTypeA& p) const noexcept = 0;
		virtual void render(const GameTypeB& p) const noexcept = 0;
	};

	struct GameTypeA : public GameBase {	// first derived game class
		void renderOn(const Renderer& renderer) const {
			renderer.render(*this);
		}
	};

	struct GameTypeB : public GameBase {	// second derived game class
		void renderOn(const Renderer& renderer) const {
			renderer.render(*this);
		}
	};

	struct GUIRenderer : public Renderer {
		void render(const GameTypeA& p) const noexcept {
			printf("Render GameTypeA on GUI.\n");
		}
		void render(const GameTypeB& p) const noexcept {
			printf("Render GameTypeB on GUI.\n");
		}
	};

	struct CLIRenderer : public Renderer {
		void render(const GameTypeA& p) const noexcept {
			printf("Render GameTypeA on cli.\n");
		}
		void render(const GameTypeB& p) const noexcept {
			printf("Render GameTypeB on cli.\n");
		}
	};

	GUIRenderer gui;
	CLIRenderer cli;

	GameTypeA a;
	GameTypeB b;

	GameBase *p_currentGameType = &a;
	p_currentGameType->renderOn(cli);
	p_currentGameType->renderOn(gui);

	p_currentGameType = &b;
	p_currentGameType->renderOn(cli);
	p_currentGameType->renderOn(gui);

	std::cout << "Finished Succesfully\n";
	return EXIT_SUCCESS;
}

