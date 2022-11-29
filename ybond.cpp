// Student Name: Yeana Bond
// New source file 1

using namespace std;
#include <iostream>

// in order to call rand() and srand()
#include <cstdlib>
// in order to use time()
#include <ctime>



int show_my_name()
{
    cout << "Yeana.\n" << endl;
    return 0;
}



// Oct 25 update

float change_snake_color()
{
    srand (static_cast <unsigned> (time(NULL)));
    cout << "Press k to change the snake color.\n" << endl;

    //From:  https://www.demo2s.com/cpp/cpp-float-c-static-cast-float-loops-floor-loops.html
    //The below line 
    float change = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    // cout << change << "\n" <<  endl;

    return change;


}

