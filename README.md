# TUP25 Project Manager

## Descripción

Este proyecto implementa un sistema de gestión de tareas y proyectos en C usando listas enlazadas. Permite crear, buscar y eliminar proyectos y tareas, y listar todo el contenido.

## Integrantes del Grupo

-   @agostinaj1:Agostina Jara
-   @SofiaSVBD: Sofia Svoboda
-   @GACB-Ar: Geronimo Angel Cespedes Bochle

---

## Requisitos

- **Windows 10/11**
- **PowerShell** habilitado
- Compilador C instalado y agregado al PATH:
  - ✅ [MinGW-w64 (recomendado)](https://www.mingw-w64.org/)
  - ✅ [TDM-GCC](https://jmeubank.github.io/tdm-gcc/)
- El archivo `compile_program.ps1` debe estar ubicado en el mismo directorio que los archivos `.c`

---

## Instrucciones para Compilar y Ejecutar

1. Asegúrate de tener `gcc` accesible desde PowerShell. Puedes verificarlo con:

   ```powershell
   gcc --version
   ```

   Si el comando falla, revisa que tu instalación de **MinGW-w64** o **TDM-GCC** esté correctamente agregada al **PATH del sistema**.

2. Abre PowerShell y navega al directorio del proyecto:

   ```powershell
   cd C:\ruta\a\TUP25_projectmanager
   ```

3. Ejecuta el script de compilación:

   ```powershell
   ./compile_program.ps1
   ```

4. Ejecuta el programa:

   ```powershell
   ./project_manager.exe
   ```

---

## Limpieza

Para borrar el ejecutable generado:

```powershell
Remove-Item .\project_manager.exe -ErrorAction SilentlyContinue
```

---

## Notas adicionales

- Si necesitas agregar MinGW-w64 o TDM-GCC al PATH:
  1. Busca la carpeta donde está `gcc.exe` (por ejemplo: `C:\TDM-GCC-64\bin` o `C:\mingw64\bin`)
  2. Agrega esa ruta al PATH del sistema:
     - Abrir **Panel de control** → Sistema → Configuración avanzada → Variables de entorno.
     - Editar la variable `Path` en el **área del sistema** o del **usuario**.
  3. Reinicia PowerShell para que tome los cambios.
