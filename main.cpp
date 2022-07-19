#include <stdio.h>
#include "vectornav.h"

const char* const COM_PORT = "\\\\.\\COM3";
const int BAUD_RATE = 115200;

int main(void)
{
    Vn200 vn200;
	VnDeviceCompositeData data;

    vn200_connect(&vn200, COM_PORT, BAUD_RATE);
    vn200_setAsynchronousDataOutputType(
        &vn200,
        //VNASYNC_VNYMR,
        VNASYNC_VNGPS,
        true);
    Sleep(1000);
	
    for (int i=0;i<1000;i++) {

        VN_ERROR_CODE err = vn200_getCurrentAsyncData(&vn200, &data);
        if (err != VNERR_NO_ERROR) {
            printf("Error on vn200_getCurrentAsyncData: %d\n", err);
        }
        else {

            printf("Orientation YawPitchRoll: %+#7.2f %+#7.2f %+#7.2f\n", data.ypr.yaw, data.ypr.pitch, data.ypr.roll);
            printf("Acceleration XYZ: %+#7.2f %+#7.2f %+#7.2f\n", data.acceleration.c0, data.acceleration.c1, data.acceleration.c2);
            printf("Location: %+#7.2f %+#7.2f %+#7.2f\n", data.latitudeLongitudeAltitude.c0, data.latitudeLongitudeAltitude.c1, data.latitudeLongitudeAltitude.c2);
        }

        Sleep(10);
    }

    vn200_disconnect(&vn200);
    
    return 0;
}
