// STD
#include <memory>

// OGRE
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <OgreColourValue.h>

// OIS
#include <OIS.h>

// MyGUI
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

void setupResourcesPath(std::auto_ptr<Ogre::Root>& root, const Ogre::String& fileName) {
    Ogre::ConfigFile cf;
    cf.load(fileName);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}

class InputListener : public OIS::MouseListener {
public:
	virtual ~InputListener() {}
	virtual bool mouseMoved(const OIS::MouseEvent &arg) {
		MyGUI::InputManager::getInstance().injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);
		return true;
	}
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
		MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
		return true;
	}
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
		MyGUI::InputManager::getInstance().injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
		return true;
	}

};

int main(int argc, char ** argv) {
	Ogre::String configFileName = "";
	Ogre::String pluginsFileName = "plugins.cfg";
	Ogre::String logFileName = "ogre.log";
	Ogre::String resourcesFileName = "resources.cfg";

	std::auto_ptr<Ogre::Root> root(new Ogre::Root(pluginsFileName, configFileName, logFileName));

	setupResourcesPath(root, resourcesFileName);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	const Ogre::RenderSystemList& renderers = root->getAvailableRenderers();

	if (renderers.size() == 0) {
		Ogre::LogManager::getSingleton().logMessage("No renderers available");
		return 1;
	}

	root->setRenderSystem(renderers[0]);

	Ogre::RenderWindow *window = NULL;

	root->initialise(false, "", "");

	window = root->createRenderWindow("Wysypisko", 1024, 768, false, NULL);

	Ogre::SceneManager *scene = root->createSceneManager(Ogre::ST_GENERIC, "WysypiskoSceneManager");
	Ogre::SceneNode *rootNode = scene->getRootSceneNode();
	Ogre::Camera *camera = scene->createCamera("Camera");
	Ogre::SceneNode *cameraNode = rootNode->createChildSceneNode("CameraNode");
	cameraNode->attachObject(camera);

	struct {float width, height, left, top, zOrder;} viewParams = {1, 1, 0, 0, 100};

	viewParams.left = (1.0f - viewParams.width) * 0.5f;
	viewParams.top = (1.0f - viewParams.height) * 0.5f;

	Ogre::Viewport *viewport = window->addViewport(
			camera, viewParams.zOrder, viewParams.left, viewParams.top,
			viewParams.width, viewParams.height);

	viewport->setAutoUpdated(true);
	viewport->setBackgroundColour(Ogre::ColourValue(0.1,0.2,0.1));
	camera->setAspectRatio(float(viewport->getActualWidth()) / float(viewport->getActualHeight()));
	camera->setNearClipDistance(1.5f);
	camera->setFarClipDistance(3000.0f);

//	window->setActive(true);
//	window->setAutoUpdated(true);
//	root->clearEventTimes();
//	root->renderOneFrame();

	// inicjalizacja GUI
	MyGUI::OgrePlatform* guiPlatform = new MyGUI::OgrePlatform();

	//guiPlatform->getRenderManagerPtr()->OgreRenderManager
	guiPlatform->initialise(window, scene);
	MyGUI::Gui *gui = new MyGUI::Gui();
	gui->initialise();

	MyGUI::LayoutManager::getInstance().loadLayout("MainMenu.xml");

	//MyGUI::ButtonPtr button = gui->createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main");
	//button->setCaption("exit");

	window->setActive(true);

	// input
	size_t x11Handle = 0;
	window->getCustomAttribute("WINDOW", &x11Handle);
	OIS::InputManager *input = OIS::InputManager::createInputSystem(x11Handle);
	OIS::Mouse *mouse = static_cast<OIS::Mouse*>(input->createInputObject(OIS::OISMouse, true));
	InputListener inputListener;
	mouse->setEventCallback(&inputListener);
	//OIS::Keyboard *keyboard = static_cast<OIS::Keyboard*>(input->createInputObject(OIS::OISKeyboard, true));

	const OIS::MouseState &mouseState = mouse->getMouseState();

	while (!window->isClosed()) {

		mouseState.width = window->getWidth();
		mouseState.height = window->getHeight();
		mouse->capture();
		Ogre::WindowEventUtilities::messagePump();


		window->update(true);
		root->renderOneFrame();
	}

	gui->shutdown();
	delete gui;
	guiPlatform->shutdown();
	delete guiPlatform;

	return 0;
}

