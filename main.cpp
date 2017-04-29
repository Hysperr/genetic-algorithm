/**
 * This program demonstrates the genetic algorithm to maximize our function f(x)= x^2.
 * We do this in a series of 5 steps:
 *
 * (1) Randomly generate candidates
 * (2) Apply fitness function/evaluate & sort
 * (3) Crossover
 * (4) Mutate
 * (5) Repeat
 *
 * These steps give us the ability to find optimized solutions to difficult problems when we don’t know the exact answer.
 * This program uses bitstrings as candidates. Of course we can know by looking that a candidate bitstring of 11111
 * (given a max bitstring length of 5) would maximize our fitness function f(x) = x^2, because 11111 (31 in decimal) is f(31) = 961.
 * However this program is meant to show the procedure of the GA and provide any reference necessary.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>


int candidates = 6;
int candidateSize = 5;
float keep = 0.5;
float mutateRate = 0.2;

struct sample {
    std::string code;
    int value;
    int eval;
};

/**
 * Convert the string bitstr, a binary string, to an integer and return its value
 * (i.e. if bitstr = "01000", returns 8
 * @param bitstr
 * @return
 */
int bitStr_toInt(std::string bitstr) {
    int value = 0;
    int power = 0;
    for (int i = (int) (bitstr.size() - 1); i >= 0; i--)
        value += (pow(2, power++) * (bitstr[i] - '0'));  // char # - '0' gives its integer representation. See ASCII table
    return value;
}

/**
 * Perform fitness evaluation of the candidate, using fitness function (in this case, f(x) = x^2).
 * @param value
 * @return
 */
int evaluate(int value) {
    return (int) pow(value, 2);
}

/**
 * selection sort samples from largest to smallest
 * @param vector
 */
void selection_sort(std::vector<sample> &vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
        for (int j = i; j < vec.size(); j++) {
            if (vec[i].eval < vec[j].eval) {
                sample tmp = vec[i];
                vec[i] = vec[j];
                vec[j] = tmp;
            }
        }
    }
}

/**
 * Take best candidates and cross corresponding values at
 * each end of the bitstring to simulate genetic offspring.
 * @param vec
 */
void crossover(std::vector<sample> &vec) {
    std::vector<sample> results;

    // 6 candidates total. we loop on half since we modify two at a time.
    for (int i = 0; i < (candidates * keep); i++) {

        // only choose samples from the top 'keep' candidates.
        // they are top since we sorted the best at the top (beginning of vector).
        sample one = vec[(rand() % candidates) * keep];
        sample two = vec[(rand() % candidates) * keep];

        // build new candidates, initialize values
        sample r1;
        sample r2;

        r1.code = "";
        r1.value = 0;
        r1.eval = -1;

        r2.code = "";
        r2.value = 0;
        r2.eval = -1;

        // choose cut point for crossing
        int cut = rand() % candidateSize;

        // loop for crossover
        for (int j = 0; j < candidateSize; j++) {
            if (j < cut) {      // normal lateral movement
                r1.code += one.code[j];
                r2.code += two.code[j];
            }
            else {              // now crossover
                r1.code += two.code[j];
                r2.code += one.code[j];
            }
        }

        // convert values to integers and evaluate to finish up the new results
        r1.value = bitStr_toInt(r1.code);
        r2.value = bitStr_toInt(r1.code);

        r1.eval = evaluate(r1.value);
        r2.eval = evaluate(r1.value);


        results.push_back(r1);
        results.push_back(r2);
    }

    // store results of results vector into original vector
    for (int i = 0; i < results.size(); i++)
        vec[i] = results[i];
}

/**
 * Perform mutation by flipping a random bit while making sure it conforms
 * to the mutation rate (x < mutationRate)
 * @param vec
 */
void mutate(std::vector<sample> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        // should we mutate?
        if ( ((rand() % 10) / (float) 10 ) < mutateRate) {
            // which element to mutate
            int mutateIndex = rand() % candidateSize;
            // mutate
            vec[i].code[mutateIndex] = (vec[i].code[mutateIndex] == '0') ? '1' : '0';
        }
    }
}

/**
 * Print our samples
 * @param vec
 */
void showSamples(std::vector<sample> &vec) {
    for(unsigned int i = 0; i < vec.size(); i++){
        std::cout << "Sample-" << i << " : "<< vec[i].code <<" \t|\t";
        std::cout << "Value-" << i << " : "<< vec[i].value << " \t|\t";
        std::cout << "Eval-" << i << " : "<< vec[i].eval << std::endl;
    }
    std::cout << '\n';
}


int main() {
    srand((unsigned int) time(NULL));

    std::cout << "Genetic Algorithm" << std::endl;
    std::vector<sample> sample_vector;

    //generate sample population
    for (int i = 0; i < candidates; i++) {

        sample tempSample;
        tempSample.code = "";
        tempSample.value = 0;
        tempSample.eval = -1;

        for (int j = 0; j < candidateSize; j++) {
            int chance = rand() % 100;
            if (chance >= 50)
                tempSample.code += "1";
            else
                tempSample.code += "0";

        }

        sample_vector.push_back(tempSample);

    }

    // convert to decimal
    for (unsigned int i = 0; i < sample_vector.size(); i++)
        sample_vector[i].value = bitStr_toInt(sample_vector[i].code);

    // evaluate samples using fitness function.
    for (unsigned int i = 0; i < sample_vector.size(); i++)
        sample_vector[i].eval = evaluate(sample_vector[i].value);

    // output the samples
    std::cout << "\nSamples GENERATED..." << '\n';
    showSamples(sample_vector);

    // sort
    selection_sort(sample_vector);
    std::cout << "After samples are SORTED..." << '\n';
    showSamples(sample_vector);

    // crossover
    crossover(sample_vector);

    std::cout << "After CROSSOVER..." << '\n';
    showSamples(sample_vector);

    // mutate
    mutate(sample_vector);

    std::cout << "After MUTATION..." << '\n';
    showSamples(sample_vector);


    return 0;
}
