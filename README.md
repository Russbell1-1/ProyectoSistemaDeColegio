# Sistema de Notas de Colegio

Sistema de gestión de notas para estudiantes y profesores, desarrollado en C++ usando POO y archivos de texto.

---

## Características

### Para estudiantes:
- Iniciar sesión con contraseña.
- Registrarse (con código autorizado).
- Ver datos personales.
- Ver notas por materia.

### Para profesores:
- Iniciar sesión con contraseña.
- Ver datos personales.
- Registrar notas por materia.
- Calcular promedio del curso.
- Obtener la nota más alta del curso.
- (Pendiente) Ordenar lista de estudiantes por apellido.

---

## Archivos de datos
| Archivo | Contenido |
|---------|-----------|
| `Estudiantes.txt` | DNI, nombres, apellidos, código, año, contraseña |
| `Profesores.txt` | Nombre, materia, contraseña |
| `Notas.txt` | Código estudiante, materia, nota |
| `codigos.txt` | Códigos válidos para registro de estudiantes |

---

## Requisitos
- Compilador de C++11 o superior.
- Sistema operativo: Windows o Linux (consola).
- IDE recomendado: Code::Blocks, Dev-C++, Visual Studio o cualquier compilador compatible.

---

## Instalación y ejecución

1. **Compilar:**
```
g++ -o sistemaNotas main.cpp
```
2. **Ejecutar:**
```
./reportes   # Linux/Mac
SistemadeColegios_1.exe # Windows
```
3. **Cargar datos iniciales:**
- `Estudiantes.txt` → agregar estudiantes.
- `Profesores.txt` → agregar profesores.
- `codigos.txt` → agregar códigos para permitir registro.
- Las notas se registran desde el menú de profesores (`Notas.txt`).

---

## Menús

### Menú Principal:
```
A. Ingresar como estudiante
B. Ingresar como profesor
X. Salir
```

### Menú Estudiante:
```
A. Ver datos
B. Ver notas
X. Salir
```

### Menú Profesor:
```
A. Ver mis datos
B. Registrar notas
C. Promedio de mi curso
D. Nota más alta
X. Salir
```

---

## Ejemplo de uso

1. Iniciar el programa.
2. Estudiante: ingresar código y contraseña.
3. Profesor: ingresar contraseña.
4. Registrar notas, consultar promedio o nota más alta.

---

## Tecnologías
- C++ (POO)
- Archivos de texto (`ifstream` / `ofstream`)
- Vectores dinámicos (`std::vector`)
- Control de flujo y menús en consola

---

## Próximas mejoras
- Ordenar estudiantes por apellido (Quicksort).
- Generar reporte completo de estudiante con promedio y materias pendientes.
- Validaciones más robustas para ingreso de notas.
- Interfaz gráfica opcional (GUI).

---

## Autores
**Nombres:** Alexander Efrain Contreras Rodriguez - Russbell Juan Pablo Arratia Paz
**Curso:** Programación Avanzada
**Universidad / Instituto:** Universidad Nacional Jorge Basadre Grohmann

