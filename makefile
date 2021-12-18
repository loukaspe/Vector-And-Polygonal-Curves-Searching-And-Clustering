OBJS    = main_search.o main_search_clustering.o ParametersFileReader.o NearestNeighbourSolver.o InnerProductCalculator.o Logger.o HashTableCurve.o HashTableCube.o HashTable.o HashFunctionH.o HashFunctionG.o HashFunctionF.o HashFunctionCalculator.o Grid.o Generator.o FileReader.o DistanceCalculator.o DataSet.o DataLine.o DataCurve.o CommandLineParser.o ClusteringSolver.o 
OUT     = search cluster

OBJS0   = main_search.o ParametersFileReader.o NearestNeighbourSolver.o InnerProductCalculator.o Logger.o HashTableCurve.o HashTableCube.o HashTable.o HashFunctionH.o HashFunctionG.o HashFunctionF.o HashFunctionCalculator.o Grid.o Generator.o FileReader.o DistanceCalculator.o DataSet.o DataLine.o DataCurve.o CommandLineParser.o
SOURCE0 = main_search.cpp ParametersFileReader.cpp NearestNeighbourSolver.cpp InnerProductCalculator.cpp Logger.cpp HashTableCurve.cpp HashTableCube.cpp HashTable.cpp HashFunctionH.cpp HashFunctionG.cpp HashFunctionF.cpp HashFunctionCalculator.cpp Grid.cpp Generator.cpp FileReader.cpp DistanceCalculator.cpp DataSet.cpp DataLine.cpp DataCurve.cpp CommandLineParser.cpp
HEADER0 = ParametersFileReader.h NearestNeighbourSolver.h Logger.h InnerProductCalculator.h HashTableCurve.h HashTableCube.h HashTable.h HashFunctionH.h HashFunctionG.h HashFunctionF.h HashFunctionCalculator.h errors.h Grid.h Generator.h FileReader.h DistanceCalculator.h DataSet.h DataLine.h DataCurve.h CommandLineParser.h
OUT0    = search

OBJS1   = main_search_clustering.o ParametersFileReader.o NearestNeighbourSolver.o InnerProductCalculator.o Logger.o HashTableCurve.o HashTableCube.o HashTable.o HashFunctionH.o HashFunctionG.o HashFunctionF.o HashFunctionCalculator.o Grid.o Generator.o FileReader.o DistanceCalculator.o DataSet.o DataLine.o DataCurve.o CommandLineParser.o ClusteringSolver.o
SOURCE1 = main_search_clustering.cpp arametersFileReader.cpp NearestNeighbourSolver.cpp InnerProductCalculator.cpp Logger.cpp HashTableCurve.cpp HashTableCube.cpp HashTable.cpp HashFunctionH.cpp HashFunctionG.cpp HashFunctionF.cpp HashFunctionCalculator.cpp Grid.cpp Generator.cpp FileReader.cpp DistanceCalculator.cpp DataSet.cpp DataLine.cpp DataCurve.cpp CommandLineParser.cpp ClusteringSolver.cpp 
HEADER1 = ParametersFileReader.h NearestNeighbourSolver.h Logger.h InnerProductCalculator.h HashTableCurve.h HashTableCube.h HashTable.h HashFunctionH.h HashFunctionG.h HashFunctionF.h HashFunctionCalculator.h errors.h Grid.h Generator.h FileReader.h DistanceCalculator.h DataSet.h DataLine.h DataCurve.h CommandLineParser.h ClusteringSolver.h
OUT1    = cluster

CC       = g++
FLAGS    = -g -c -Wall
LFLAGS   = 

all: search cluster

search: $(OBJS0) $(LFLAGS)
	$(CC) -g $(OBJS0) -o $(OUT0)

cluster: $(OBJS1) $(LFLAGS)
	$(CC) -g $(OBJS1) -o $(OUT1)

main_search.o: main_search.cpp
	$(CC) $(FLAGS) main_search.cpp

ParametersFileReader.o: ParametersFileReader.cpp
	$(CC) $(FLAGS) ParametersFileReader.cpp

CommandLineParser.o: CommandLineParser.cpp
	$(CC) $(FLAGS) CommandLineParser.cpp
DataLine.o: DataLine.cpp
	$(CC) $(FLAGS) DataLine.cpp
	
DataSet.o: DataSet.cpp
	$(CC) $(FLAGS) DataSet.cpp
	
DataCurve.o: DataCurve.cpp
	$(CC) $(FLAGS) DataCurve.cpp

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
	
HashTableCurve.o: HashTableCurve.cpp
	$(CC) $(FLAGS) HashTableCurve.cpp
	
HashTableCube.o: HashTableCube.cpp
	$(CC) $(FLAGS) HashTableCube.cpp

InnerProductCalculator.o: InnerProductCalculator.cpp
	$(CC) $(FLAGS) InnerProductCalculator.cpp

NearestNeighbourSolver.o: NearestNeighbourSolver.cpp
	$(CC) $(FLAGS) NearestNeighbourSolver.cpp

Logger.o: Logger.cpp
	$(CC) $(FLAGS) Logger.cpp
	
Grid.o: Grid.cpp
	$(CC) $(FLAGS) Grid.cpp
	
main_search_clustering.o: main_search_clustering.cpp
	$(CC) $(FLAGS) main_search_clustering.cpp

ParametersFileReader.o: ParametersFileReader.cpp
	$(CC) $(FLAGS) ParametersFileReader.cpp

CommandLineParser.o: CommandLineParser.cpp
	$(CC) $(FLAGS) CommandLineParser.cpp
DataLine.o: DataLine.cpp
	$(CC) $(FLAGS) DataLine.cpp
	
DataSet.o: DataSet.cpp
	$(CC) $(FLAGS) DataSet.cpp
	
DataCurve.o: DataCurve.cpp
	$(CC) $(FLAGS) DataCurve.cpp

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
	
HashTableCurve.o: HashTableCurve.cpp
	$(CC) $(FLAGS) HashTableCurve.cpp
	
HashTableCube.o: HashTableCube.cpp
	$(CC) $(FLAGS) HashTableCube.cpp

InnerProductCalculator.o: InnerProductCalculator.cpp
	$(CC) $(FLAGS) InnerProductCalculator.cpp

NearestNeighbourSolver.o: NearestNeighbourSolver.cpp
	$(CC) $(FLAGS) NearestNeighbourSolver.cpp

Logger.o: Logger.cpp
	$(CC) $(FLAGS) Logger.cpp
	
Grid.o: Grid.cpp
	$(CC) $(FLAGS) Grid.cpp

ClusteringSolver.o: ClusteringSolver.cpp
	$(CC) $(FLAGS) ClusteringSolver.cpp
	
clean:
	rm -f $(OBJS) $(OUT) output.txt
