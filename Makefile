CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pthread

SOURCES := main.cpp configuracion.cpp controles.cpp simulacion.cpp \
           hebras.cpp diagnostico.cpp verificador.cpp mediciones.cpp

rw: $(SOURCES) lectores_escritores.hpp
	$(CXX) $(CXXFLAGS) $(SOURCES) -o rw

clean:
	rm -f rw

.PHONY: clean