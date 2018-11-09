#include <stdio.h>
#include "api_robot.h"

void segue_parede();
void write_motors (motors_t motors, unsigned char speed_right, unsigned char speed_left);

/*  Flag que indica o modo de operacao.
 *      flag_segue_parede == 0 se o modo é busca_parede
 *      flag_segue_parede == 1 se o modo é segue_parede
 */
char flag_segue_parede;

typedef struct motors_t{
    motor_cfg_t motor_right;
    motor_cfg_t motor_left;
} motors_t;


void segue_parede(){

    flag_segue_parede = 0;
    motors_t motors;
    motorsmotor_right.id = 1;
    motors.motor_left.id = 0;

    /*  Inicializamos os dois motores com a mesma velocidade para andar
     *  em linha reta.
     */
    write_motors(motors, 30, 30);

    while (1){

        /*  Detectamos a menor distancia entre os dos sonares à frente
         *  do robô.
         */
        int distance_right = read_sonar(4);
        int distance_left = read_sonar(3);
        int smaller_distance;
        if (distance_right > distance_left)
            smaller_distance = distance_left;
        else
            smaller_distance = distance_right;

        /*  Se a menor distância for menor que a limite, o robô entra no
         *  modo segue_parede e vira para a esquerda até que a distância
         *  detectada pelo sonar à direita seja menor ou igual que a
         *  menor distancia.
         */
        if (smaller_distance < 1300){
            flag_segue_parede = 1;
            write_motors(motors, 20, 0);
            while (read_sonar(7) >= smaller_distance){
                continue;
            }
            write_motors(motors, 30, 30);
        }

        /*  Se o robô estiver no modo segue_parede e estiver se afastando
         *  da parede, ele vira para a direita até que a distancia
         *  detectada pelo sonar à direita seja menor ou igual que a menor
         *  distancia.
         */
        if (flag_segue_parede == 1 && read_sonar(7) > 1300){
            smaller_distance = read_sonar(11);
            write_motors(motors, 0, 20);
            while (read_sonar(7) >= smaller_distance){
                continue;
            }
            write_motors(motors, 30, 30);
        }
    }

}


void write_motors (motors_t motors, unsigned char speed_right, unsigned char speed_left){
    motors.motor_right.speed = speed_right;
    motors.motor_left.speed = speed_left;
    set_motor_speed(motors.motor_right);
    set_motor_speed(motors.motor_left);
}
