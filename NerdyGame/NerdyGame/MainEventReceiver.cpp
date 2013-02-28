#include <irrlicht.h>
#include "NetworkBoy.h"
#include <SFML\Network.hpp>
#include <wchar.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
	IrrlichtDevice *device;
	s32				counter;
	IGUIListBox*	listbox;
	NetworkBoy*		networkBoy;
	irr::gui::IGUIEditBox* ipBox;
	irr::gui::IGUIButton* connect;
	irr::gui::IGUIButton* makeserver;
};

// Define some values that we'll use to identify individual GUI controls.
enum
{
	GUI_ID_CONNECT_BUTTON = 101,
	GUI_ID_IPBAR,
	GUI_ID_MAKESERVER_BUTTON
};

class MainEventReceiver : public IEventReceiver
{
public:
	MainEventReceiver(SAppContext & context) : Context(context) { }

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{
			/*
			If a button was clicked, it could be one of 'our'
			three buttons. If it is the first, we shut down the engine.
			If it is the second, we create a little window with some
			text on it. We also add a string to the list box to log
			what happened. And if it is the third button, we create
			a file open dialog, and add also this as string to the list box.
			That's all for the event receiver.
			*/
			case EGET_BUTTON_CLICKED:
				switch(id)
				{

				case GUI_ID_CONNECT_BUTTON:
					{
						wchar_t wc = *Context.ipBox->getText();
						wcslen(&wc);
						char* c = new char();
						wctomb(c, wc);

						sf::IpAddress adress(c);
						
						Context.networkBoy->connect(adress);

						delete c;
					}
				break;

				case GUI_ID_MAKESERVER_BUTTON:
					{
						Context.networkBoy->setupServer();
						Context.makeserver->setVisible(false);
						Context.connect->setVisible(false);
						Context.ipBox->setVisible(false);
					}

				default:
					return false;
				}
				break;

			case EGET_FILE_SELECTED:
				{
					// show the model filename, selected in the file dialog
					IGUIFileOpenDialog* dialog =
						(IGUIFileOpenDialog*)event.GUIEvent.Caller;
					Context.listbox->addItem(dialog->getFileName());
				}
				break;

			default:
				break;
			}
		}

		return false;
	}

private:
	SAppContext & Context;
};