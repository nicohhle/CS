#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

void readData(const string &filename, vector<double> &angle, vector<double> &lift) {
    ifstream windFile;
    double num1;
    double num2;
    
    windFile.open(filename.c_str());
    
    if (!windFile.is_open() ) {
        cout << "Error opening " << filename << endl;
        exit(1);
    }
    
    while (windFile >> num1 >> num2) {
        angle.push_back(num1);
        lift.push_back(num2);
    }
    
    windFile.close();
}

double interpolation(double value, const vector<double> &angle, const vector<double> &lift) {
    
    double fb = 0; //lift for angle B;
    double fa; //lift for angle A;
    double fc; //lift for angle C;
    
    double a; //angle A;
    double b; //angle B;
    double c; //angle C;
    
    for (unsigned int i = 0; i < angle.size(); ++i) {
        if (angle.at(i) == value) {
            return lift.at(i);
        } else {
            if (angle.at(0) <= value && angle.at(1) >= value) {
                fa = lift.at(0);
                fc = lift.at(1);
                a = angle.at(0);
                b = value;
                c = angle.at(1);
                
                fb = fa + (((b - a) / (c - a)) * (fc - fa));
                
            } else if (angle.at(angle.size() - 2) <= value && angle.at(angle.size() - 1) >= value) {
            fa = lift.at(angle.size() - 2);
            fc = lift.at(angle.size() - 1);
            a = angle.at(angle.size() - 2);
            b = value;
            c = angle.at(angle.size() - 1);
            
            fb = fa + (((b - a) / (c - a)) * (fc - fa));
            
            } else {
                
                for (unsigned int j = 0; j < angle.size(); ++j) {
                    if (value >= angle.at(j) && value <= angle.at(j + 1)) {
                        fa = lift.at(j); 
                        fc = lift.at(j + 1);
                        a = angle.at(j);
                        b = value;
                        c = angle.at(j + 1);
                        
                        fb = fa + (((b - a) / (c - a)) * (fc - fa));
                    }
                }
            }
        }
    }
    
    return fb;
}

bool isOrdered(const vector<double> &angle) {
    
    for (unsigned int i = 1; i < angle.size(); ++i) {
        if (angle.at(i) < angle.at(i - 1)) {
            return false;
        }
    }
    
    return true;
}

void reorder(vector<double> &angle, vector<double> &lift) {
    
    double temp = 0;
    double temp2 = 0;
    
    for (unsigned int i = 0; i < angle.size(); ++i) {
        for (unsigned int j = 0; j < angle.size() - 1; ++j) {
            if (angle.at(j) > angle.at(j + 1)) {
                temp = angle.at(j);
                temp2 = lift.at(j);
                
                angle.at(j) = angle.at(j + 1);
                lift.at(j) = lift.at(j + 1);
                
                angle.at(j + 1) = temp;
                lift.at(j + 1) = temp2;
            }
        }
    }
}

int main() {
    vector<double> angle;
    vector<double> lift;
    
    string filename;
    double value;
    
    cout << "Enter name of input data file:" << endl;
    cin >> filename;
    cout << endl;
    
    readData(filename, angle, lift);
    
    cout << "Enter flight angle: " << endl;
    cin >> value;
    cout << endl;
    
    for (unsigned int i = 0; i < angle.size(); ++i) {
        lift.at(i) = interpolation(value, angle, lift);
    }
    
    if (!isOrdered(angle)) {
        reorder(angle, lift);
    }

    for (unsigned int i = 0; i < angle.size(); ++i) {
        cout << angle.at(i) << " " << lift.at(i) << endl;
    }

    return 0;
}