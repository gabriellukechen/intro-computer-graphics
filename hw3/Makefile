CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
CFLAGS = -g -DGL_GLEXT_PROTOTYPES -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED -DOSX -Wno-deprecated-register -Wno-deprecated-declarations -Wno-shift-op-parentheses
INCFLAGS = -I./glm-0.9.7.1 -I/usr/X11/include -I./include/
LDFLAGS = -framework GLUT -framework OpenGL -L./lib/mac/ \
		-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
		-lGL -lGLU -lm -lstdc++ -lfreeimage
else
CFLAGS = -g -DGL_GLEXT_PROTOTYPES 
INCFLAGS = -I./glm-0.9.7.1 -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L./lib/nix/ \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lGLEW -lglut -lGLU -lGL -lX11 -lfreeimage
endif

RM = /bin/rm -f 
all: transforms
transforms: main.o Transform.o readfile.o Sampler.o Ray.o Camera.o RaytracerA.o SurfaceIntersectionInfo.o variables.h readfile.h Transform.h
	$(CC) $(CFLAGS) -o transforms main.o Transform.o Sampler.o Ray.o Camera.o SurfaceIntersectionInfo.o RaytracerA.o readfile.o $(INCFLAGS) $(LDFLAGS)
main.o: main.cpp Transform.h variables.h Sampler.h Ray.h Camera.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
readfile.o: readfile.cpp readfile.h variables.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c readfile.cpp
Transform.o: Transform.cpp Transform.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Transform.cpp
Sampler.o: Sampler.cpp variables.h Sampler.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sampler.cpp
Ray.o: Ray.cpp Ray.h Transform.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Ray.cpp
Camera.o: Camera.cpp Camera.h variables.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Camera.cpp
RaytracerA.o: RaytracerA.cpp RaytracerA.h variables.h Camera.h SurfaceIntersectionInfo.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c RaytracerA.cpp
SurfaceIntersectionInfo.o: SurfaceIntersectionInfo.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c SurfaceIntersectionInfo.cpp
clean:
	$(RM) *.o transforms *.png


 
