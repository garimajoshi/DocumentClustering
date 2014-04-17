PROGRAM = DocumentClustering

CC = g++
CFLAGS = -c -Wall
LDFLAGS =
SOURCES = main.cpp Document.cpp DocumentVector.cpp DocumentCollection.cpp DocumentClustering.cpp Centroid.cpp VectorSpaceModel.cpp StopWordsHandler.cpp SimilarityMatrics.cpp
OBJECTS = $(SOURCES:.cpp = .o)
EXECUTABLE = clustering

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o clustering