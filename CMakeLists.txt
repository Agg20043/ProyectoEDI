cmake_minimum_required(VERSION 4.1)
project(untitled3)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled3 main.cpp
        controlador/persona.cpp
        modelo/persona.h
        controlador/pruebaPersona.cpp
        modelo/pruebaPersona.h
        controlador/Fecha.cpp
        modelo/Fecha.h
        controlador/Artista.cpp
        modelo/Artista.h
        controlador/cancion.cpp
        modelo/cancion.h
        controlador/pruebaArtista.cpp
        modelo/pruebaArtista.h
        modelo/PlayList.h
        controlador/PlayList.cpp
        modelo/GestorUsuario.h
        modelo/PruebaPlaylist.h
        controlador/PruebaPlaylist.cpp
        controlador/GestorUsuario.cpp
        modelo/PruebaGestorUsuarios.h
        controlador/PruebaGestorUsuarios.cpp
        modelo/GestorArtista.h
        controlador/GestorArtista.cpp
        modelo/Sistema.h
        controlador/Sistema.cpp
        modelo/PruebaSistema.h
        controlador/PruebaSistema.cpp
        controlador/progPrincipal.cpp
)
