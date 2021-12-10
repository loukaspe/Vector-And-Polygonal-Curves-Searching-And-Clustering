#include <iostream>
#include <cfloat>
#include <chrono>
#include <map>

#include "ClusteringSolver.h"

ClusteringSolver::ClusteringSolver(DataSet & input, string outputfile) : input(input), outputFile(outputfile) {

}

ClusteringSolver::~ClusteringSolver() {

}

void ClusteringSolver::printInitialState(ClusteringSolver::Cluster * initialState, int clusters) {
    cout << "Initial State: " << endl;

    for (int i = 0; i < clusters; i++) {
        cout << "Cluster: " << i << endl;

        cout << "Center: ";
        for (int j = 0; j < initialState[i].center->getDimension(); j++) {
            cout << initialState[i].center->data[j] << ",";
        }
        cout << "..." << endl;
    }

    cout << endl;
}

void ClusteringSolver::print(ClusteringSolver::Cluster * initialState, int clusters, bool complete, int t[]) {
    Logger *logger = new Logger(this->outputFile);
    stringstream ss;

    ss << "Algorithm: " << algorithm << endl;
    log(&ss, logger);

    cout << "Final State: " << endl;

    for (int i = 0; i < clusters; i++) {
        ss << "CLUSTER-: " << i << endl;
        log(&ss, logger);

        ss << "\tsize: " << initialState[i].indices.size() << endl;
        log(&ss, logger);

        ss << "\tcentroid: ";
        log(&ss, logger);
        for (int j = 0; j < initialState[i].center->getDimension(); j++) {
            ss << initialState[i].center->data[j] << ",";
            log(&ss, logger);
        }

        ss << endl;
        log(&ss, logger);

        if (complete) {
            ss << "\titem ids: ";
            log(&ss, logger);

            for (unsigned j = 0; j < initialState[i].indices.size(); j++) {
                ss << input.lines[initialState[i].indices[j]].id << "\t";
                log(&ss, logger);
            }
        }

        ss << "\tclustering_time: " << t[i]  << endl;
        log(&ss, logger);

        ss << "\tSilhoutte: " << initialState[i].silhouette << endl;
        log(&ss, logger);
    }

    ss << endl;
    log(&ss, logger);
    logger->close();
}

ClusteringSolver::Cluster * ClusteringSolver::initialization(int clusters) {
    int n = (int) input.lines.size();
    int d = input.lines[0].getDimension();

    cout << "Initialization ... " << endl;

    ClusteringSolver::Cluster * initialState = new ClusteringSolver::Cluster[clusters]();

    DistanceCalculator calc(false);

    for (int i = 0; i < clusters; i++) {
        if (i == 0) { // first centroid
            int index = urandom(0, n - 1);
            initialState[0].center = new DataLine();

            for (int i = 0; i < d; i++) {
                initialState[0].center->data.push_back(input.lines[index].data[i]);
            }

            cout << "Picked: " << index << endl;
        } else {
            float * pr = new float[n];

            for (int x = 0; x < n; x++) { // for each item
                float mindist = FLT_MAX;

                for (int y = 0; y < i; y++) {
                    double dist = calc.calculateDistance(input.lines[x], *(initialState[y].center));
                    if (dist < mindist) {
                        mindist = dist;
                    }
                }

                if (x == 0) {
                    pr[x] = mindist;
                } else {
                    pr[x] = mindist + pr[x - 1];
                }
            }

            float min = 0.0f;
            float max = pr[n - 1];

            //            cout << "min: " << min << ", max: " << max << endl;

            float r = urandomf(min, max);
            int x;

            for (x = 0; x < n; x++) { // for each item
                if (r <= pr[x] && (x == 0 || pr[x - 1] < r)) {
                    break;
                }
            }

            int index = x;
            initialState[i].center = new DataLine();

            for (int j = 0; j < d; j++) {
                initialState[i].center->data.push_back(input.lines[index].data[j]);
            }

            delete [] pr;

            cout << "Picked: " << index << endl;
        }
    }

    return initialState;
}

ClusteringSolver::Cluster * ClusteringSolver::update(ClusteringSolver::Cluster * now, int clusters) {
    ClusteringSolver::Cluster * nextState = new ClusteringSolver::Cluster[clusters]();

    cout << "Update ... " << endl;

    for (int y = 0; y < clusters; y++) { // for each cluster
        nextState[y].center = new DataLine();

        for (unsigned d = 0; d < now->center->data.size(); d++) {
            float sum = 0;
            int counter = 0;

            for (unsigned i = 0; i < now[y].indices.size(); i++) {
                sum += input.lines[now[y].indices[i]].data[d];
                counter++;
            }

            sum /= counter;

            nextState[y].center->data.push_back(sum);
        }
    }

    return nextState;
}

ClusteringSolver::Cluster * ClusteringSolver::lloyd(int clusters, int t[]) {
    DistanceCalculator calc(false);

    algorithm = "Lloyd";
    // ----------------------------------
    //          1. Initialization
    // ----------------------------------
    ClusteringSolver::Cluster * currentState = initialization(clusters);

    printInitialState(currentState, clusters);

    int n = (int) input.lines.size();

    auto start = chrono::steady_clock::now();

    for (int counter = 0; counter < 20; counter++) { // Clustering loop
        // ----------------------------------
        //          2. Assignment
        // ----------------------------------

        cout << "Assignment ... " << endl;
        for (int x = 0; x < n; x++) { // for each item
            float mindist = FLT_MAX;
            int mincluster = 0;

            for (int y = 0; y < clusters; y++) { // for each cluster
                double dist = calc.calculateDistance(input.lines[x], *(currentState[y].center));
                if (dist < mindist) {
                    mindist = dist;
                    mincluster = y;
                }
            }

            currentState[mincluster].indices.push_back(x);
        }

        // ----------------------------------
        //          3. Update
        // ----------------------------------

        if (counter < 19) {
            ClusteringSolver::Cluster * nextState = update(currentState, clusters);

            delete [] currentState;

            currentState = nextState;
        }
    }

    auto end = chrono::steady_clock::now();

    t[0] = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    return currentState;
}

ClusteringSolver::Cluster * ClusteringSolver::lsh(int clusters, int t[], int number_of_vector_hash_tables, int number_of_vector_hash_functions, int W) {
    DistanceCalculator calc(false);

    algorithm = "LSH";

    // ---------------------------------------
    //          1a. Initialization - Kmeans++
    // ---------------------------------------
    ClusteringSolver::Cluster * currentState = initialization(clusters);

    printInitialState(currentState, clusters);

    int n = (int) input.lines.size();

    // ---------------------------------------
    //          1b. Initialization - LSH
    // ---------------------------------------

    int T = n / 8;

    NearestNeighbourSolver solver(input);

    HashTable * hashtables = solver.prepareHashtables(number_of_vector_hash_tables, T, number_of_vector_hash_functions, W);

    auto start = chrono::steady_clock::now();


    // ----------------------------------------------------
    //          1c. Initialization - Reverse approach LSH
    // ----------------------------------------------------
    map<int, int> item_cluster; // item -> cluster_id
    map<int, float> item_distance; // item -> distance from cluster
    map<int, double> item_loop_found; // item -> radius found

    for (unsigned i = 0; i < input.lines.size(); i++) {
        item_loop_found[i] = -1;
    }

    bool change;

    for (int counter = 0; counter < 20; counter++) { // Clustering loop

        // ----------------------------------
        //          2. Assignment
        // ----------------------------------
        cout << "Assignment ... " << endl;

        for (unsigned i = 0; i < input.lines.size(); i++) {
            item_distance[i] = FLT_MAX;
            item_cluster[i] = -1;
        }

        DataSet query;

        for (int i = 0; i < clusters; i++) {
            query.lines.push_back(*currentState[i].center);
        }

        double R = DBL_MAX;


        for (int i = 0; i < clusters; i++) {
            for (int j = 0; j < clusters; j++) {
                if (i == j) {
                    continue;
                }

                double dist = calc.calculateDistance(*currentState[i].center, *currentState[j].center);

                if (dist < R) {
                    R = dist;
                }
            }
        }

        R = R / 2;

        change = true;

        while (change == true) { // Reverse approach loop
            change = false;

            cout << "Scanning in R = " << R << endl;

            vector<NearestNeighbourSolver::NearestNeighbor> * result_lsh = solver.lsh(hashtables, query, number_of_vector_hash_tables, T, number_of_vector_hash_functions, W);

//            cout << "result lsh " << R << endl;

            for (int cluster_id = 0; cluster_id < clusters; cluster_id++) {
                unsigned j = 0;

                cout << result_lsh[cluster_id].size() << endl;
                while (j < result_lsh[cluster_id].size() && sqrt(result_lsh[cluster_id][j].distance) <= R) {
//                    cout << "loop j = " << j << endl;
                    int index = result_lsh[cluster_id][j].index;

                    if (item_cluster[index] == -1) { // first time discovered
                        item_cluster[index] = cluster_id;
                        item_distance[index] = result_lsh[cluster_id][j].distance;
                        item_loop_found[index] = R;
                        change = true;
//                        cout << "change " << endl;
                    } else if (item_cluster[index] == cluster_id) { // already discovered by me
                        // do nothing
//                        cout << "nothing to me" << endl;
                    } else { // discovered by someone else
                        if (item_loop_found[index] < R) {
                            // do nothing
//                            cout << "nothing R" << endl;
                        } else if (item_loop_found[index] == R) {
                            double dist = calc.calculateDistance(input.lines[index], *(currentState[cluster_id].center));
                            if (dist < item_loop_found[index]) {
                                item_cluster[index] = cluster_id;
                                item_distance[index] = result_lsh[cluster_id][j].distance;
                                item_loop_found[index] = R;
                                change = true;
//                                cout << "change " << endl;
                            }
                        }
                    }
                    j++;
                }
            }

            R = R * 2;
        }

        cout << " --- lloyd --- " << endl;

        for (map<int, int>::iterator it = item_cluster.begin(); it != item_cluster.end(); ++it) {
            if (it->second == -1) { // point not assigned to anyone
                int x = it->first;
                float mindist = FLT_MAX;
                int mincluster = 0;

                for (int y = 0; y < clusters; y++) { // for each cluster
                    double dist = calc.calculateDistance(input.lines[x], *(currentState[y].center));
                    if (dist < mindist) {
                        mindist = dist;
                        mincluster = y;
                    }
                }

                currentState[mincluster].indices.push_back(x);
            } else {
                currentState[it->second].indices.push_back(it->first);
            }
        }

        // ----------------------------------
        //          3. Update
        // ----------------------------------

        if (counter < 19) {
            ClusteringSolver::Cluster * nextState = update(currentState, clusters);

            delete [] currentState;

            currentState = nextState;
        }
    }


    auto end = chrono::steady_clock::now();

    t[0] = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    delete [] hashtables;

    return currentState;
}

ClusteringSolver::Cluster * ClusteringSolver::cube(int clusters, int t[], int number_of_vector_hash_tables, int number_of_vector_hash_functions, int W, int max_number_M_hypercube, int number_of_hypercube_dimensions, int number_of_probes) {
    DistanceCalculator calc(false);

    algorithm = "HYPERCUBE";

    // ---------------------------------------
    //          1a. Initialization - Kmeans++
    // ---------------------------------------
    ClusteringSolver::Cluster * currentState = initialization(clusters);

    printInitialState(currentState, clusters);

    int n = (int) input.lines.size();
    int no_of_g = (int)log2(input.lines.size());

    // ---------------------------------------
    //          1b. Initialization - Hypercube
    // ---------------------------------------

    int T = n / 8;

    NearestNeighbourSolver solver(input);

    HashTable * hashtables = solver.prepareHyperCube(no_of_g, T, number_of_vector_hash_functions, W);

    auto start = chrono::steady_clock::now();


    // ----------------------------------------------------
    //          1c. Initialization - Reverse approach Hypercube
    // ----------------------------------------------------
    map<int, int> item_cluster; // item -> cluster_id
    map<int, float> item_distance; // item -> distance from cluster
    map<int, double> item_loop_found; // item -> radius found

    for (unsigned i = 0; i < input.lines.size(); i++) {
        item_loop_found[i] = -1;
    }

    bool change;

    for (int counter = 0; counter < 20; counter++) { // Clustering loop

        // ----------------------------------
        //          2. Assignment
        // ----------------------------------
        cout << "Assignment ... " << endl;

        for (unsigned i = 0; i < input.lines.size(); i++) {
            item_distance[i] = FLT_MAX;
            item_cluster[i] = -1;
        }

        DataSet query;

        for (int i = 0; i < clusters; i++) {
            query.lines.push_back(*currentState[i].center);
        }

        double R = DBL_MAX;


        for (int i = 0; i < clusters; i++) {
            for (int j = 0; j < clusters; j++) {
                if (i == j) {
                    continue;
                }

                double dist = calc.calculateDistance(*currentState[i].center, *currentState[j].center);

                if (dist < R) {
                    R = dist;
                }
            }
        }

        R = R / 2;

        change = true;

        while (change == true) { // Reverse approach loop
            change = false;

            cout << "Scanning in R = " << R << endl;

            vector<NearestNeighbourSolver::NearestNeighbor> * result_cube = solver.cube(hashtables, query, no_of_g, max_number_M_hypercube, number_of_probes, T, number_of_vector_hash_functions, W);

            cout << "result cube " << R << endl;

            for (int cluster_id = 0; cluster_id < clusters; cluster_id++) {
                unsigned j = 0;

                cout << result_cube[cluster_id].size() << endl;
                while (j < result_cube[cluster_id].size() && sqrt(result_cube[cluster_id][j].distance) <= R) {
//                    cout << "loop j = " << j << endl;
                    int index = result_cube[cluster_id][j].index;

                    if (item_cluster[index] == -1) { // first time discovered
                        item_cluster[index] = cluster_id;
                        item_distance[index] = result_cube[cluster_id][j].distance;
                        item_loop_found[index] = R;
                        change = true;
//                        cout << "change " << endl;
                    } else if (item_cluster[index] == cluster_id) { // already discovered by me
                        // do nothing
//                        cout << "nothing to me" << endl;
                    } else { // discovered by someone else
                        if (item_loop_found[index] < R) {
                            // do nothing
//                            cout << "nothing R" << endl;
                        } else if (item_loop_found[index] == R) {
                            double dist = calc.calculateDistance(input.lines[index], *(currentState[cluster_id].center));
                            if (dist < item_loop_found[index]) {
                                item_cluster[index] = cluster_id;
                                item_distance[index] = result_cube[cluster_id][j].distance;
                                item_loop_found[index] = R;
                                change = true;
//                                cout << "change " << endl;
                            }
                        }
                    }
                    j++;
                }
            }

            R = R * 2;
        }

        cout << " --- lloyd --- " << endl;

        for (map<int, int>::iterator it = item_cluster.begin(); it != item_cluster.end(); ++it) {
            if (it->second == -1) { // point not assigned to anyone
                int x = it->first;
                float mindist = FLT_MAX;
                int mincluster = 0;

                for (int y = 0; y < clusters; y++) { // for each cluster
                    double dist = calc.calculateDistance(input.lines[x], *(currentState[y].center));
                    if (dist < mindist) {
                        mindist = dist;
                        mincluster = y;
                    }
                }

                currentState[mincluster].indices.push_back(x);
            } else {
                currentState[it->second].indices.push_back(it->first);
            }
        }

        // ----------------------------------
        //          3. Update
        // ----------------------------------

        if (counter < 19) {
            ClusteringSolver::Cluster * nextState = update(currentState, clusters);

            delete [] currentState;

            currentState = nextState;
        }
    }


    auto end = chrono::steady_clock::now();

    t[0] = chrono::duration_cast<chrono::milliseconds>(end - start).count();


    delete [] hashtables;

    return currentState;
}

void log(stringstream *logs, Logger* logger) {
    cout << logs->str();
    logger->log(logs->str());
    logs->str(std::string());
}

void ClusteringSolver::silhouette(ClusteringSolver::Cluster * lastState, int clusters, int t[]) {
    DistanceCalculator calc(false);

    for (int best_cluster = 0; best_cluster < clusters; best_cluster++) { // for each cluster
        cout << "calculating silhouettte for cluster: " << best_cluster << " ..." << endl;

        double avg_s = 0;
        int counter = 0;

        for (unsigned x = 0; x < lastState[best_cluster].indices.size(); x++) { // for each point of the best cluster
            // find second best
            float mindist = FLT_MAX;
            int secondbest_cluster = 0;

            for (int y = 0; y < clusters; y++) { // for each cluster other than the best
                if (y != best_cluster) {
                    double dist = calc.calculateDistance(input.lines[ lastState[best_cluster].indices[x]], *(lastState[y].center));
                    if (dist < mindist) {
                        mindist = dist;
                        secondbest_cluster = y;
                    }
                }
            }

            // second best is now known

            // find avg distance from best cluster points

            double a = 0;

            for (unsigned x2 = 0; x2 < lastState[best_cluster].indices.size(); x2++) { // for each point of the best cluster
                a += calc.calculateDistance(input.lines[ lastState[best_cluster].indices[x]], input.lines[lastState[best_cluster].indices[x2]]);
            }

            if (lastState[best_cluster].indices.size() > 0) {
                a /= (lastState[best_cluster].indices.size() - 1);
            }

            // find avg distance from second best cluster points

            double b = 0;

            for (unsigned x2 = 0; x2 < lastState[secondbest_cluster].indices.size(); x2++) { // for each point of the best cluster
                b += calc.calculateDistance(input.lines[ lastState[best_cluster].indices[x]], input.lines[lastState[secondbest_cluster].indices[x2]]);
            }

            if (lastState[secondbest_cluster].indices.size() > 0) {
                b /= lastState[secondbest_cluster].indices.size();
            }

            double s = 0;

            if (max(b, a) != 0) {
                s = (b - a) / max(b, a);
            }


            avg_s += s;
            counter++;
        }

        if (counter > 0) {
            avg_s /= counter;
        }

        lastState[best_cluster].silhouette = avg_s;
    }
}