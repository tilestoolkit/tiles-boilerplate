#include "Template_Device.h"

Template_Device::Template_Device()
{
    //Constructor code
}

void Template_Device::HandleTime(unsigned int  ElapsedTime)
{
    Template_Device_Timing += ElapsedTime;
}

void Template_Device::RefreshValues()
{
    if(Template_Device_Timing > RefreshThreshold)
    {

      Template_Device_Timing = 0;
    }

}