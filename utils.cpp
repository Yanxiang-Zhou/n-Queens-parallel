#include "utils.h"

bool input_sanity_check(std::ostringstream& err_msg, int argc, char **argv) {

    int n,k,e;

    err_msg << "\n";

    if (argc!=4) {
        err_msg << "usage: " << argv[0] << " n k e" << std::endl;
        return false;
    }

    n=atoi(argv[1]);
    k=atoi(argv[2]);
    e=atoi(argv[3]);

    if (n<0) {
        err_msg << "ERROR: n should be greater than zero" << std::endl;
        return false;
    }
    if (k<0) {
        err_msg << "ERROR: k should be greater than zero" << std::endl;
        return false;
    }
    if (e<0) {
        err_msg << "ERROR: e should be greater than or equal to zero" << std::endl;
        return false;
    }
    if (n<k) {
        err_msg << "ERROR: n should be greater than or equal to k" << std::endl;
        return false;
    }

    return true;
}

void write_output(  std::ostream& os,
                    double time_elapsed,
                    unsigned int exit_on_first,
                    std::vector<std::vector<unsigned int> >& solns) {

    if (exit_on_first) {
      os << "-1" << std::endl;
    } else {
      os << solns.size() << std::endl;
    }
    if (solns.size() == 0) {
        return;
    }
    unsigned int nq = solns[0].size();
    for (unsigned int i=0; i < solns.size(); i++) {
        for (unsigned int j=0; j < nq - 1; j++) {
            os << solns[i][j] << " ";
        }
        os << solns[i][nq-1];
        os << std::endl;
    }

}
