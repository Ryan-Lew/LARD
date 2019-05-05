#include "consolecontrol.h"

ConsoleControl::ConsoleControl()
{

}

void ConsoleControl::onMessageHandler(QByteArray contant)
{
    if(contant.size() > 0 && contant.size() < 7)
    {
        char funcnum = contant.at(2);
        switch ((int)funcnum)
        {
        case Ctl_AT_PORT:
        {

            break;
        }
        case Ctl_AT_STBD:
        {

            break;
        }
        case Ctl_PT_PORT:
        {

            break;
        }
        case Ctl_PT_STBD:
        {

            break;
        }
        case Ctl_MIC_PLAY:
        {

            break;
        }
        case Ctl_MIC_REC:
        {

            break;
        }
        case Ctl_WARNING:
        {

            break;
        }
        case Ctl_DEFENCE:
        {

            break;
        }
        case Ctl_VOICE:
        {

            break;
        }
        case Ctl_STOP_BTN:
        {

            break;
        }
        default:
        {

            break;
        }
        }
    }
    else if(contant.size() >= 7)
    {
        //遥感控制
    }

}
