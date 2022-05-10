/* 
Test code on double dispatch design pattern in a dynamic way, during runtime.
Used to render a board game serie in cli or gui mode.
Note that C++ cannot directly support double dispatch.

by Tassos 2022
*/

#include <iostream>

int main() {
	struct Renderer;	// forward declaration

	struct Paixnidi {	// pure abstruct game base class 
	public:
		virtual void renderOn(const Renderer& renderer) const = 0;
	};

	struct Portes; struct Plakoto;	// forward declarations of game types

	struct Renderer { // pure abstruct base class of renderers of games
		virtual void render(const Portes& p) const noexcept = 0;
		virtual void render(const Plakoto& p) const noexcept = 0;
	};

	struct Portes : public Paixnidi {	// first derived game class
		void renderOn(const Renderer& renderer) const {
			renderer.render(*this);
		}
	};

	struct Plakoto : public Paixnidi {	// second derived game class
		void renderOn(const Renderer& renderer) const {
			renderer.render(*this);
		}
	};


	struct GUIRenderer : public Renderer {
		void render(const Portes& p) const noexcept {
			printf("Render portes on GUI.\n");
		}
		void render(const Plakoto& p) const noexcept {
			printf("Render plakoto on GUI.\n");
		}
	};

	struct CLIRenderer : public Renderer {
		void render(const Portes& p) const noexcept {
			printf("Render portes on cli.\n");
		}
		void render(const Plakoto& p) const noexcept {
			printf("Render plakoto on cli.\n");
		}
	};

	GUIRenderer gui;
	CLIRenderer cli;

	Portes por;
	Plakoto pla;

	Paixnidi *p_currentGameType = &por;
	p_currentGameType->renderOn(cli);
	p_currentGameType->renderOn(gui);

	p_currentGameType = &pla;
	p_currentGameType->renderOn(cli);
	p_currentGameType->renderOn(gui);

	printf("Finished Succesfully\n");
    return EXIT_SUCCESS;
}

