// STD
#include <memory>

// OGRE
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>

// MyGUI
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

int main(int argc, char ** argv) {
	Ogre::String configFileName = "";
	Ogre::String pluginsFileName = "plugins.cfg";
	Ogre::String logFileName = "ogre.log";

	std::auto_ptr<Ogre::Root> pRoot(
			new Ogre::Root(pluginsFileName, configFileName, logFileName));

	const Ogre::RenderSystemList& renderers = pRoot->getAvailableRenderers();

	if (renderers.size() == 0) {
		Ogre::LogManager::getSingleton().logMessage("No renderers available");
		return 1;
	}

	pRoot->setRenderSystem(renderers[0]);

	Ogre::RenderWindow *window = NULL;

	pRoot->initialise(false, "", "");

	window = pRoot->createRenderWindow("Wysypisko", 1024, 768, false, NULL);

	while (!window->isClosed()) {
		Ogre::WindowEventUtilities::messagePump();
	}

	return 0;
}

