OBJS    = main_lsh.o main_cube.o main_clustering.o Logger.o ParametersFileReader.o CommandLineParser.o DataLine.o DataSet.o DistanceCalculator.o FileReader.o Generator.o HashFunctionCalculator.o HashFunctionH.o HashTable.o HashFunctionG.o HashFunctionF.o InnerProductCalculator.o NearestNeighbourSolver.o  ClusteringSolver.o
OUT     = lsh cube cluster

OBJS0   = main_lsh.o Logger.o CommandLineParser.o DataLine.o DataSet.o DistanceCalculator.o FileReader.o Generator.o HashFunctionCalculator.o HashFunctionH.o HashTable.o HashFunctionG.o InnerProductCalculator.o NearestNeighbourSolver.o
SOURCE0 = main_lsh.cpp Logger.cpp CommandLineParser.cpp DataLine.cpp DataSet.cpp DistanceCalculator.cpp FileReader.cpp Generator.cpp HashFunctionCalculator.cpp HashFunctionH.cpp HashFunctionG.cpp HashTable.cpp InnerProductCalculator.cpp NearestNeighbourSolver.cpp
HEADER0 = CommandLineParser.h Logger.h Dataline.h DataSet.h DistanceCalculator.h errors.h FileReader.h Generator.h HashFunctionCalculator.h HashFunctionH.h HashFunctionG.h HashTable.h InnerProductCalculator.h NearestNeighbourSolver.h
OUT0    = lsh

OBJS1   = main_cube.o Logger.o CommandLineParser.o DataLine.o DataSet.o DistanceCalculator.o FileReader.o Generator.o HashFunctionCalculator.o HashFunctionH.o HashFunctionG.o HashFunctionF.o HashTable.o InnerProductCalculator.o NearestNeighbourSolver.o
SOURCE1 = main_cube.cpp Logger.cpp CommandLineParser.cpp DataLine.cpp DataSet.cpp DistanceCalculator.cpp FileReader.cpp Generator.cpp HashFunctionCalculator.cpp HashFunctionH.cpp HashFunctionG.cpp HashFunctionF.cpp HashTable.cpp InnerProductCalculator.cpp NearestNeighbourSolver.cpp
HEADER1 = CommandLineParser.h Logger.h Dataline.h DataSet.h DistanceCalculator.h errors.h FileReader.h Generator.h HashFunctionCalculator.h HashFunctionH.h HashFunctionG.h HashFunctionF.h HashTable.h HashTable_1.h InnerProductCalculator.h NearestNeighbourSolver.h
OUT1    = cube

OBJS2   = main_clustering.o Logger.o ParametersFileReader.o CommandLineParser.o DataLine.o DataSet.o DistanceCalculator.o FileReader.o Generator.o HashFunctionCalculator.o HashFunctionH.o HashTable.o HashFunctionG.o HashFunctionF.o InnerProductCalculator.o NearestNeighbourSolver.o  ClusteringSolver.o
SOURCE2 = main_clustering.cpp Logger.cpp ParametersFileReader.cpp CommandLineParser.cpp DataLine.cpp DataSet.cpp DistanceCalculator.cpp FileReader.cpp Generator.cpp HashFunctionCalculator.cpp HashFunctionH.cpp HashTable.cpp HashFunctionF.cpp HashFunctionG.cpp InnerProductCalculator.cpp NearestNeighbourSolver.cpp  ClusteringSolver.cpp
HEADER2 = CommandLineParser.h Logger.h ParametersFileReader.h Dataline.h DataSet.h DistanceCalculator.h errors.h FileReader.h Generator.h HashFunctionCalculator.h HashFunctionH.h HashFunctionF.h HashFunctionG.h HashTable.h HashTable_1.h InnerProductCalculator.h NearestNeighbourSolver.h ClusteringSolver.h
OUT2   = cluster

CC       = g++
FLAGS    = -g -c -Wall
LFLAGS   = 

all: lsh cube cluster

lsh: $(OBJS0) $(LFLAGS)
	$(CC) -g $(OBJS0) -o $(OUT0)

cube: $(OBJS1) $(LFLAGS)
	$(CC) -g $(OBJS1) -o $(OUT1)

cluster: $(OBJS2) $(LFLAGS)
	$(CC) -g $(OBJS2) -o $(OUT2)

main_lsh.o: main_lsh.cpp
	$(CC) $(FLAGS) main_lsh.cpp

CommandLineParser.o: CommandLineParser.cpp
	$(CC) $(FLAGS) CommandLineParser.cpp

DataLine.o: DataLine.cpp
	$(CC) $(FLAGS) DataLine.cpp
	
DataSet.o: DataSet.cpp
	$(CC) $(FLAGS) DataSet.cpp

DistanceCalculator.o: DistanceCalculator.cpp
	$(CC) $(FLAGS) DistanceCalculator.cpp

FileReader.o: FileReader.cpp
	$(CC) $(FLAGS) FileReader.cpp

Generator.o: Generator.cpp
	$(CC) $(FLAGS) Generator.cpp

HashFunctionCalculator.o: HashFunctionCalculator.cpp
	$(CC) $(FLAGS) HashFunctionCalculator.cpp

HashFunctionH.o: HashFunctionH.cpp
	$(CC) $(FLAGS) HashFunctionH.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) HashTable.cpp

InnerProductCalculator.o: InnerProductCalculator.cpp
	$(CC) $(FLAGS) InnerProductCalculator.cpp

NearestNeighbourSolver.o: NearestNeighbourSolver.cpp
	$(CC) $(FLAGS) NearestNeighbourSolver.cpp

main_cube.o: main_cube.cpp
	$(CC) $(FLAGS) main_cube.cpp

CommandLineParser.o: CommandLineParser.cpp
	$(CC) $(FLAGS) CommandLineParser.cpp

DataLine.o: DataLine.cpp
	$(CC) $(FLAGS) DataLine.cpp

DataSet.o: DataSet.cpp
	$(CC) $(FLAGS) DataSet.cpp

DistanceCalculator.o: DistanceCalculator.cpp
	$(CC) $(FLAGS) DistanceCalculator.cpp

FileReader.o: FileReader.cpp
	$(CC) $(FLAGS) FileReader.cpp

Generator.o: Generator.cpp
	$(CC) $(FLAGS) Generator.cpp

HashFunctionCalculator.o: HashFunctionCalculator.cpp
	$(CC) $(FLAGS) HashFunctionCalculator.cpp

HashFunctionH.o: HashFunctionH.cpp
	$(CC) $(FLAGS) HashFunctionH.cpp

HashFunctionG.o: HashFunctionG.cpp
	$(CC) $(FLAGS) HashFunctionG.cpp

HashFunctionF.o: HashFunctionF.cpp
	$(CC) $(FLAGS) HashFunctionF.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) HashTable.cpp

InnerProductCalculator.o: InnerProductCalculator.cpp
	$(CC) $(FLAGS) InnerProductCalculator.cpp

NearestNeighbourSolver.o: NearestNeighbourSolver.cpp
	$(CC) $(FLAGS) NearestNeighbourSolver.cpp

main_cluster.o: main_cluster.cpp
	$(CC) $(FLAGS) main_cluster.cpp

CommandLineParser.o: CommandLineParser.cpp
	$(CC) $(FLAGS) CommandLineParser.cpp

DataLine.o: DataLine.cpp
	$(CC) $(FLAGS) DataLine.cpp

DataSet.o: DataSet.cpp
	$(CC) $(FLAGS) DataSet.cpp

DistanceCalculator.o: DistanceCalculator.cpp
	$(CC) $(FLAGS) DistanceCalculator.cpp

FileReader.o: FileReader.cpp
	$(CC) $(FLAGS) FileReader.cpp

Generator.o: Generator.cpp
	$(CC) $(FLAGS) Generator.cpp

HashFunctionCalculator.o: HashFunctionCalculator.cpp
	$(CC) $(FLAGS) HashFunctionCalculator.cpp

HashFunctionH.o: HashFunctionH.cpp
	$(CC) $(FLAGS) HashFunctionH.cpp

HashFunctionG.o: HashFunctionG.cpp
	$(CC) $(FLAGS) HashFunctionG.cpp

HashFunctionF.o: HashFunctionF.cpp
	$(CC) $(FLAGS) HashFunctionF.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) HashTable.cpp

InnerProductCalculator.o: InnerProductCalculator.cpp
	$(CC) $(FLAGS) InnerProductCalculator.cpp

NearestNeighbourSolver.o: NearestNeighbourSolver.cpp
	$(CC) $(FLAGS) NearestNeighbourSolver.cpp

ClusteringSolver.o: ClusteringSolver.cpp
	$(CC) $(FLAGS) ClusteringSolver.cpp

ParametersFileReader.o: ParametersFileReader.cpp
	$(CC) $(FLAGS) ParametersFileReader.cpp

Logger.o: Logger.cpp
	$(CC) $(FLAGS) Logger.cpp

clean:
	rm -f $(OBJS) $(OUT) output.txt
