#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

int IC, PTR, VA, RA, kio = -1, flag[30], PI, TI, SI, TTC = 0, LLC = 0;
char M[300][4], IR[4], R[4], C;
char page[10][4];
fstream fin, fout;
char temp[100];
string line;
void MOS();

struct PCB {
    char job[4], TTL[4], TLL[4];
} pcb;

int ttl, tll;

void endprogram() {
    fout << "\nSI = " << SI << "  TI =" << TI << "  PI=" << PI << endl;
    fout << "TTC = " << TTC << "  LLC=" << LLC << endl;
    cout << "\nSI = " << SI << "  TI =" << TI << "  PI=" << PI << endl;
    cout << "TTC = " << TTC << "  LLC=" << LLC << endl;
    exit(1);
}

void allocate() {
    int pos, i, j, k = 0, check = 0;
    char str[2];
    int level = 0;

    while (check != 1) {
        kio++;
        pos = (rand() % 29) * 10;
        while (flag[pos / 10] != 0) {
            pos = (rand() % 29) * 10;
        }
        flag[pos / 10] = 1;
        itoa(pos, str, 10);
        if (pos / 100 == 0) {
            M[PTR + kio][2] = '0';
            M[PTR + kio][3] = str[0];
        } else {
            M[PTR + kio][2] = str[0];
            M[PTR + kio][3] = str[1];
        }
        getline(fin, line);
        level++;
        k = 0;
        for (i = 0; i < line.size() / 4; i++) {
            for (j = 0; j < 4; j++) {
                M[pos + i][j] = line[k];
                k++;
                if (line[k] == 'H') {
                    check = 1;
                    M[pos + (i + 1)][0] = 'H';
                    M[pos + (i + 1)][1] = '0';
                    M[pos + (i + 1)][2] = '0';
                    M[pos + (i + 1)][3] = '0';
                }
            }
        }
    }
    cout << endl << "MEMORY" << endl;
    for (i = 0; i < 300; i++) {
        cout << "[" << i << "] = ";
        for (j = 0; j < 4; j++) {
            cout << M[i][j];
        }
        cout << endl;
    }
}

void AddMap() {
    char str[2];
    RA = PTR + (VA / 10);

    if (M[RA][3] == '#') {
        cout << "**** Page fault occurred ****\n";

        int pos = (rand() % 29) * 10;
        while (flag[pos / 10] != 0) {
            pos = (rand() % 29) * 10;
        }
        flag[pos / 10] = 1;
        itoa(pos, str, 10);
        if (pos / 100 == 0) {
            M[RA][2] = '0';
            M[RA][3] = str[0];
        } else {
            M[RA][2] = str[0];
            M[RA][3] = str[1];
        }
        PI = 3;
    }

    if (RA > PTR + 10) {
        PI = 2;
        MOS();
    }
}

void read() {
    int no, i, j, k = 0;

    getline(fin, line);
    cout << "\nLine  :" << line;
    no = ((M[RA][2] - 48) * 10) + (M[RA][3] - 48);
    no = no * 10;

    for (i = 0; k <= line.size(); i++) {
        for (j = 0; j < 4 && k <= line.size(); j++) {
            M[no + i][j] = line[k];
            k++;
        }
    }

    for (i = 0; i < 300; i++) {
        cout << "[" << i << "] = ";
        for (j = 0; j < 4; j++) {
            cout << M[i][j];
        }
        cout << endl;
    }
}

void write() {
    char buff[40];
    cout << "\n In Write : \n";
    int no = ((M[RA][2] - 48) * 10) + (M[RA][3] - 48);
    no = no * 10;
    int k = 0;

    while (1) {
        for (int i = 0; i < 4; i++) {
            if (M[no][i] == '_') break;
            buff[k] = M[no][i];
            k++;
        }
        if (M[no][i] == '_') break;
        no++;
    }
    buff[k] = '\0';
    cout << "\n Line is : " << buff << endl;
    fout.write(buff, strlen(buff));
    cout << "program terminated normally";
    fout << endl << "-----------------------------------------------------------------------------------" << endl;
    fout << endl << "program terminated normally" << endl;
}

void MOS() {
    if (PI == 1) {
        cout << "\n**** Opcode Error : ****\n**** Program terminated abnormally. ****\n\n";
        fout << "\n**** Opcode error : ****\n**** Program terminated abnormally. ****";
        endprogram();
    } else if (PI == 2) {
        cout << "\n**** Operand Error : ****\n**** Program terminated abnormally. ****\n\n";
        fout << "\n**** Operand error : ****\n**** Program terminated abnormally. ****";
        endprogram();
    }

    if (SI == 3) {
        endprogram();
    } else if (SI == 1) {
        if (TI == 0) read();
        else if (TI == 2) {
            cout << "\n**** Time Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            fout << "\n**** Time Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            endprogram();
        }
    } else if (SI == 2) {
        if (TI == 0) {
            write();
        } else if (TI == 2) {
            write();
            cout << "\n**** Time Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            fout << "\n**** Time Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            endprogram();
        } else if (TI == 1) {
            cout << "\n**** Line Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            fout << "\n**** Line Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            endprogram();
        }
    }
}

void examine() {
    char ch = IR[0];
    PI = 0;

    switch (ch) {
        case 'G':
            if (IR[1] != 'D') {
                PI = 1;
                MOS();
            } else {
                TTC += 2;
                if (TTC <= ttl) {
                    SI = 1;
                    MOS();
                } else {
                    TI = 2;
                    MOS();
                }
            }
            break;

        case 'P':
            SI = 2;
            if (IR[1] != 'D') {
                PI = 1;
                MOS();
            } else {
                LLC++;
                TTC++;
                if (LLC < tll) {
                    TI = 0;
                    MOS();
                }
                if (TTC > ttl) {
                    TI = 1;
                    MOS();
                } else {
                    SI = 2;
                    MOS();
                }
            }
            break;

        case 'H':
            SI = 3;
            MOS();
            break;
    }
}

void executeProgram() {
    int no;
    char a[3];
    for (int i = 0; i <= kio; i++) {
        a[0] = M[PTR + i][2];
        a[1] = M[PTR + i][3];
        a[2] = '\0';
        no = ((a[0] - 48) * 10) + (a[1] - 48);
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 4; k++) {
                IR[k] = M[(no * 10) + j][k];
            }
            VA = ((IR[2] - 48) * 10) + (IR[3] - 48);
            examine();
        }
    }
}

int main() {
    fin.open("test.txt");
    fout.open("output.txt", ios::app);

    if (fin.fail()) {
        cout << "Error opening input file." << endl;
        return 1;
    }

    while (!fin.eof()) {
        fin.getline(temp, 100);
        for (int j = 0; j < 4; j++) {
            pcb.job[j] = temp[j];
        }
        pcb.TTL[0] = temp[4];
        pcb.TTL[1] = temp[5];
        pcb.TTL[2] = '\0';
        ttl = atoi(pcb.TTL);
        cout << "Total time limit = " << ttl << endl;
        pcb.TLL[0] = temp[6];
        pcb.TLL[1] = temp[7];
        pcb.TLL[2] = '\0';
        tll = atoi(pcb.TLL);
        cout << "Total line limit = " << tll << endl;
        PTR = TTC;
        allocate();
        executeProgram();
        memset(M, 0, sizeof(M)); // Clear memory after execution
        memset(flag, 0, sizeof(flag)); // Reset flags
    }

    fin.close();
    fout.close();
    return 0;
}
