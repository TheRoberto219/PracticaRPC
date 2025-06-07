/* registro_alumnos.x - Definición del servicio de registro de alumnos */
const MAX_NOMBRE = 50;
const MAX_APELLIDO = 50;
const MAX_CURSO = 30;
const MAX_ALUMNOS = 100;

struct alumno {
    int id;
    string nombre<MAX_NOMBRE>;
    string apellido<MAX_APELLIDO>;
    int edad;
    string curso<MAX_CURSO>;
};

struct busqueda {
    int id;
    string nombre<MAX_NOMBRE>;
    string apellido<MAX_APELLIDO>;
    string curso<MAX_CURSO>;
};

struct resultado_busqueda {
    int cantidad;
    alumno datos<>;
};

program REGISTRO_ALUMNOS {
    version REGISTRO_ALUMNOS_V1 {
        bool registrar_alumno(alumno) = 1;
        resultado_busqueda buscar_alumno(busqueda) = 2;
        bool actualizar_alumno(alumno) = 3;
        bool eliminar_alumno(int) = 4;
    } = 1;
} = 0x20000002;
