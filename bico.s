.align 4
.text

@   Chama a syscall 21 para ler um sonar
@   Parametro:
@       r0: identificador do sonar (0 a 15)
@   Retorno:
@       r0: -1 se o identificador do sonar for invalido
@           valor obtido na leitura, caso contrario
read_sonar:
    mov r7, #21
    svc 0x0


@   Chama a syscall 20 para alterar a velocidade do motor
@   Parametros:
@       r0: identificador do motor (0 ou 1)
@       r1: velocidade do motor (0 a 63)
@   Retorno:
@       r0: -1 se o motor for invalido
@           -2 se a velocidade for invalida
@            0 caso contrario
set_motor_speed:
    mov r7, #20
    svc 0x0


@   Chama a syscall 18 para alterar o tempo do sistema
@   Parametro:
@       r0: novo tempo do sistema
set_time:
    mov r7, #18
    svc 0x0


@   Chama a syscall 17 para ler o tempo do sistema
@   Retorno:
@       r0: tempo do sistema
get_time:
    mov r7, #17
    svc 0x0
