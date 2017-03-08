#include "elev.h"
#include <stdio.h>
#include "elevatorControl.h"


int main() {
    
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    
    printf("Press STOP button to stop elevator and exit program.\n");
    
    //printf("%d", elev_get_floor_sensor_signal());
    if (elev_get_floor_sensor_signal() == -1 ) {
        elev_set_motor_direction(DIRN_DOWN);
    }
    //kjør oppstartsprosedyre for å komme til definert tilstand
    startUp();
    
    
    //Hvis stopp knapp trykkes inn stopp
    stop();
    // åpne dører, slett bestillingsliste, og vent 3 sekunder før døren lukkes og gjør klar for nye bestilling
    
    
    
    
    
    
    
    while(1) {
        validateCounters();
        
        currentFloor();
        
        stop();
        getOrders();
        
        
        //kjøring av bestillingsliste
        if (ordersExist()) {
            runOrders();
        }
        else{
            startUp();
           
        }
        
     getOrders();
        printf("\n");
        //printf("%d", elev_get_button_signal(BUTTON_CALL_DOWN, 2));
        //printf("\n");
        
        
    }
    
    
    return 0;
}
