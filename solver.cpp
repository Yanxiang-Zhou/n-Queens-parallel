#include "solver.h"
#include <string>



/* Worker helper */

std::vector<std::vector<unsigned int>> findPermutations(std::vector<unsigned int> init, int start, int end) {
    std::vector<std::vector<unsigned int>> ans;
    if (start == end) {
        ans.push_back(init);
        return ans;
    }

    int len = init.size();
    for (int i = start; i <= end; ++i) {
        unsigned int tmp = init[start];
        init[start] = init[i];
        init[i] = tmp;

        std::vector<std::vector<unsigned int>> rec = findPermutations(init, start + 1, end);
        ans.insert(ans.end(), rec.begin(), rec.end());
    }
    return ans;
}

bool isValidSol(std::vector<unsigned int> sol) {
    for (int i = 0; i < sol.size() - 1; ++i) {
        for (int j = i + 1; j < sol.size(); ++j) {
            if (abs(j - i) == abs(sol[j] - sol[i]))
                return false;
        }
    }
    return true;
}

/* Master helper */

bool check (std::vector<unsigned int> soln, int pos){
    if (pos == 0) return true;

    int curr_row = soln[pos];
    int curr_col = pos;
    for (int i = 0; i < pos; i++){
        int row = soln[i];
        int col = i;
        if (row == curr_row || col == curr_col || abs(row - curr_row) == abs(col - curr_col)){
            return false;
        }
    }
    return true;
}


std::vector<unsigned int> tryFirstK (unsigned int n, unsigned int k){
    if (n == 1){
        return std::vector<unsigned int> (1, 0);
    }
    else{
        std::vector<unsigned int> soln(n, n+1);
        int pos = 0;
        while (pos >= 0 && pos < k){
            if (pos == 0){
                if (soln[pos] == n+1) soln[pos] = 0;
                else{
                    soln[pos] ++;

                    if (soln[pos] == n) return std::vector<unsigned int> (n, n+1);

                    for (int i = 1; i < k; i++) soln[i] = n+1;

                }
                pos ++;
            }
            else{
                if (soln[pos] == n+1) soln[pos] = 0;
                else soln[pos] ++;

                while (!check(soln, pos) && soln[pos] < n) soln[pos] ++;

                if (soln[pos] == n) {
                    soln[pos] = n+1;
                    pos --;
                }
                else pos ++;
            }
        }
        return soln;
    }
}


std::vector<unsigned int> permutation (unsigned int n, unsigned int k, std::vector<unsigned int> prev_soln){
    if (prev_soln[0] == n+1){
        return tryFirstK(n, k);
    }
    else{
        std::vector<unsigned int> soln = prev_soln;
        int pos = k-1;

        while (pos >= 0 && pos < k){
            if (pos == 0){
                soln[pos] ++;
                
                if (soln[pos] == n) return std::vector<unsigned int> (n, n+1);
                
                for (int i = 1; i < k; i++) soln[i] = n+1;

                pos ++;
            }
            else{
                if (soln[pos] == n+1) soln[pos] = 0;
                else soln[pos] ++;

                while (!check(soln, pos) && soln[pos] < n) soln[pos] ++;
                if (soln[pos] == n){
                    soln[pos] = n+1;
                    pos --;
                }
                else pos ++;
            }
        }

        return soln;
    }
}

void print_vector(std::vector<unsigned int> vec){
    int len = vec.size();
    printf("Vector Solution:\n");
    for (int i = 0; i < len; i++){
        printf("%u ", vec[i]);
    }
    printf("\n");
}

void print_array(unsigned int arr[], int len){
    printf("Size: %d, Array Solution:\n", len);
    for (int i = 0; i < len; i++){
        printf("%u ", arr[i]);
    }
    printf("\n");
}

std::vector<std::vector<unsigned int>> split_solns(int n, int num_solns, std::vector<unsigned int> tmp_solns){
    std::vector<std::vector<unsigned int>> res;
    if (num_solns == 0) return res;

    int pos = 0;
    while (num_solns > 0){
        std::vector<unsigned int> tmp_soln(n, n+1);
        
        for (int i = 0; i < n; i ++){
            // printf("value: %d ", tmp_solns[pos+i]);
            tmp_soln[i] = tmp_solns[pos+i];
        }

        res.push_back(tmp_soln);
        pos += n;
        num_solns --;
    }
    
    return res;
}

void vec_to_arr(std::vector<unsigned int> vec, unsigned int * arr){
    int vec_size = vec.size();

    for (int i = 0; i < vec_size; i++){
        arr[i] = vec[i];
    }
}


/* Sequential helper */

bool IsQueenSafe(std::vector<std::string>& positions, int row, int col, unsigned int n) {
    for (int i = row - 1, j = col; i >= 0; --i) {
        if (positions[i][j] == 'Q')
            return false;
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (positions[i][j] == 'Q')
            return false;
    }

    for (int i = row - 1, j = col + 1; i >= 0 && j <= (n - 1); --i, ++j) {
        if (positions[i][j] == 'Q')
            return false;
    }
    return true;
}

void NQueensOne(std::vector<std::vector<unsigned int> >& solns, std::vector<std::string>& positions, unsigned int n, int row, std::vector<unsigned int>& temp) {

    int a = solns.size();

    if (a==1) {
        return;
    }

    if (row == n) {
        solns.push_back(temp);
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (IsQueenSafe(positions, row, col, n) == true) {
            std::vector<unsigned int> tem1;
            tem1 = temp;
            positions[row][col] = 'Q';
            tem1.push_back(col);
            NQueensOne(solns, positions, n, row + 1, tem1);
            positions[row][col] = '.';
        }
    }
}

void NQueensAll(std::vector<std::vector<unsigned int> >& solns, std::vector<std::string>& positions, unsigned int n, int row, std::vector<unsigned int>& temp) {
    if (row == n) {
        solns.push_back(temp);
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (IsQueenSafe(positions, row, col, n) == true) {
            std::vector<unsigned int> tem2;
            tem2 = temp;
            positions[row][col] = 'Q';
            tem2.push_back(col);
            NQueensAll(solns, positions, n, row + 1, tem2);
            positions[row][col] = '.';
        }
    }

}



/*************************** solver.h functions ************************/


void seq_solver(unsigned int n, unsigned int exit_on_first, std::vector<std::vector<unsigned int> >& solns) {
    // TODO: Implement this function
    std::vector<std::string> positions(n, std::string(n, '.'));
    std::vector<unsigned int> temp;
    int row = 0;

    if (exit_on_first == false) {
        NQueensAll(solns, positions, n, row, temp);
    }
    else {
        NQueensOne(solns, positions, n, row, temp);
    }
}



void nqueen_master( unsigned int n,
                    unsigned int k,
                    unsigned int exit_on_first,
                    std::vector<std::vector<unsigned int> >& solns) {

    /* MPI_TAG: 0, signal to terminate workers 
                    val==1 => terminate worker
     *          1, signal to send/receive partial solns
     *          2, signal to send/receive complete solns
     *          4, the number of solutions returned from worker
     */
    int num_workers;
    MPI_Comm_size(MPI_COMM_WORLD, &num_workers);


    if (n == 1) {
        std::vector<unsigned int> soln(1, 0);
        solns.push_back(soln);
        return;
    }

    if (n == k){
        std::vector<unsigned int> soln(n, n+1);
        soln = permutation(n, k, soln);

        if (soln[0] != n+1){
            if (exit_on_first) 
                solns.push_back(soln);
            else
                while (soln[0] != n+1){
                    solns.push_back(soln);
                    soln = permutation(n, k, soln);
                }
            
        }

        unsigned int close_worker[n];
        for (int i = 0; i < n; i++) close_worker[i] = 0;
        for (int i = 1; i < num_workers; i ++){
            MPI_Send(&close_worker, n, MPI_UNSIGNED, i, 0, MPI_COMM_WORLD);
            printf("[Master] One terminal signal sent from master to worker %d.\n", i);
        }

        return;
    }

    std::vector<std::vector<unsigned int>> solns_sets;


    /******************* STEP 1: Send one partial solution to each worker ********************/


    int i = 1; // worker rank
    std::vector<unsigned int> partial_soln(n, n+1);
    bool enough_job_flag = true;
    bool ending_flag = false;

    if (k != 0){
        std::vector<unsigned int> test = permutation(n, k, partial_soln);
        if (test[0] == n+1) return;
    }

    if (k != 0){
        while (i < num_workers){
            partial_soln = permutation(n, k, partial_soln);
            // send job to workers
            if (partial_soln[0] != n+1){
                unsigned int partial_soln_send[n];
                vec_to_arr(partial_soln, partial_soln_send);
                // print_array(partial_soln_send, sizeof(partial_soln_send)/sizeof(partial_soln_send[0]));
                MPI_Send(&partial_soln_send, n, MPI_UNSIGNED, i, 1, MPI_COMM_WORLD);
                printf("Sending one partial solution to %d...\n", i);
                i++;
            }else{
                enough_job_flag = false;
                break;
            }  
        }
    }else{

        while (i < num_workers){
            // partial_soln = permutation(n, k, partial_soln);
            // send job to workers
            unsigned int partial_soln_send[n];
            vec_to_arr(partial_soln, partial_soln_send);
            // print_array(partial_soln_send, sizeof(partial_soln_send)/sizeof(partial_soln_send[0]));
            MPI_Send(&partial_soln_send, n, MPI_UNSIGNED, i, 1, MPI_COMM_WORLD);
            printf("Sending one partial solution to %d...\n", i);
            i++; 
            enough_job_flag = false;
        }
    }
    

    /******************* STEP 2: Send partial solutions to workers as they respond ********************/

    std::vector<unsigned int> cmplt_soln;
    int num_solns;
    int len_solns;
    std::vector<std::vector<unsigned int>> tmp_solns;

    int curr_rank;
    MPI_Status status;
    int working_procs;

    //if jobs are much sufficient
    if (enough_job_flag){
        bool no_more_job = false;
        working_procs = num_workers;

        while (!ending_flag && working_procs > 1){
            // int num_solns;
            MPI_Recv(&num_solns, 1, MPI_INT, MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &status);
 
            if (num_solns != 0) len_solns = num_solns * n;
            else len_solns = n;

            curr_rank = status.MPI_SOURCE;
            // printf("Received %d solns from worker %d.\n", num_solns, curr_rank);
        
            unsigned int cmplt_soln_recv [len_solns];
            MPI_Recv(&cmplt_soln_recv, len_solns, MPI_UNSIGNED, curr_rank, 2, MPI_COMM_WORLD, &status);
            // print_array(cmplt_soln_recv, len_solns);
            
            std::vector<unsigned int> cmplt_soln(cmplt_soln_recv, cmplt_soln_recv+len_solns);
            // if (num_solns > 0) print_vector(cmplt_soln);

            working_procs --;

            //if there is still partial soln to send
            if (!no_more_job){
                partial_soln = permutation(n, k, partial_soln);
                //if the next partial soln is valid
                if (partial_soln[0] != n+1) {
                    //send out the partial soln to the vacant proc & add this proc to the working procs
                    unsigned int partial_soln_send[n];
                    vec_to_arr(partial_soln, partial_soln_send);
                    // print_array(partial_soln_send, sizeof(partial_soln_send)/sizeof(partial_soln_send[0]));
                    MPI_Send(&partial_soln_send, n, MPI_INT, curr_rank, 1, MPI_COMM_WORLD);
                    printf("Sending another partial solution to %d...\n",curr_rank);
                    
                    working_procs ++;
                }else{ //if the next partial soln is valid

                    //consider that there is no more job to send
                    no_more_job = true;

                }
            }

            //if the received complete soln is valid
            if (num_solns > 0){
                if (exit_on_first) {
                    num_solns = 1;
                    ending_flag = true;
                    // printf("Exiting on first...");

                }
                //add the soln to the vector `solns`
                
                // printf("num_solns: %d.\n", num_solns);
                tmp_solns = split_solns(n, num_solns, cmplt_soln);
                
                while (num_solns > 0){
                    // print_vector(tmp_solns[num_solns-1]);
                    solns.push_back(tmp_solns[num_solns-1]);
                    num_solns --;
                }

                //if exit on first, then exit the loop
            }
        }
    }else{ //if there are some procs vacant & there are still workers working
        if (k != 0){   
            working_procs = i;
            while (working_procs > 1 && !ending_flag){
                //receive every complete soln from every worker
                MPI_Recv(&num_solns, 1, MPI_INT, MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &status);

                if (num_solns != 0) len_solns = num_solns * n;
                else len_solns = n;

                curr_rank = status.MPI_SOURCE;

                unsigned int cmplt_soln_recv[len_solns];
                MPI_Recv(&cmplt_soln_recv, len_solns, MPI_UNSIGNED, curr_rank, 2, MPI_COMM_WORLD, &status);
                
                std::vector<unsigned int> cmplt_soln(cmplt_soln_recv, cmplt_soln_recv+len_solns);
                //remove the worker from active workers
                working_procs --;
                //if the complete soln is valid
                
                if (num_solns > 0){
                    if (exit_on_first) {
                        // num_solns = 1;
                        ending_flag = true;
                        // printf("Exiting on first...");
                    }
                    //add the soln to the vector `solns`
                    
                    tmp_solns = split_solns(n, num_solns, cmplt_soln);
                    
                    while (num_solns > 0){
                        print_vector(tmp_solns[num_solns-1]);
                        solns.push_back(tmp_solns[num_solns-1]);
                        num_solns --;
                    }
                    //if exit on first, then exit the loop
                }
            }
        }else{

            MPI_Recv(&num_solns, 1, MPI_INT, MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &status);

            if (num_solns != 0) len_solns = num_solns * n;
            else len_solns = n;

            curr_rank = status.MPI_SOURCE;

            unsigned int cmplt_soln_recv[len_solns];
            MPI_Recv(&cmplt_soln_recv, len_solns, MPI_UNSIGNED, curr_rank, 2, MPI_COMM_WORLD, &status);
                
            std::vector<unsigned int> cmplt_soln(cmplt_soln_recv, cmplt_soln_recv+len_solns);

            if (num_solns > 0){
                if (exit_on_first) {
                    ending_flag = true;
                    // printf("Exiting on first...");
                }
                //add the soln to the vector `solns`
                    
                tmp_solns = split_solns(n, num_solns, cmplt_soln);
                    
                while (num_solns > 0){
                    print_vector(tmp_solns[num_solns-1]);
                    solns.push_back(tmp_solns[num_solns-1]);
                    num_solns --;
                }
                    //if exit on first, then exit the loop
            }

            unsigned int close_worker[n];
            for (int i = 0; i < n; i++) close_worker[i] = 0;
            for (i = 1; i < num_workers; i ++){
                if (i != curr_rank){
                    MPI_Send(&close_worker, n, MPI_UNSIGNED, i, 0, MPI_COMM_WORLD);
                    printf("[Master] One terminal signal sent from master to worker %d.\n", i);
                }
            }
        }
    }


    std::sort(solns_sets.begin(), solns_sets.begin()+solns_sets.size());

    for (int k = 0; k < solns_sets.size(); k ++) solns.push_back(solns_sets[k]);
    
    /********************** STEP 3: Terminate **************************/

    unsigned int close_worker[n];
    for (int i = 0; i < n; i++) close_worker[i] = 0;
    for (i = 1; i < num_workers; i ++){
        MPI_Send(&close_worker, n, MPI_UNSIGNED, i, 0, MPI_COMM_WORLD);
        printf("[Master] One terminal signal sent from master to worker %d.\n", i);
    }
}



void nqueen_worker( unsigned int n,
                    unsigned int k,
                    unsigned int exit_on_first) {

    // TODO: Implement this function
    if (n == 1) {
        return;
    }

    int proc_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    
    while (1) {
        unsigned int qPos[n];
        MPI_Status status;

        MPI_Recv(&qPos, n, MPI_UNSIGNED, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        // std::cout<<proc_id<<" worker "; print_array(qPos);

        int tag = status.MPI_TAG;
        if (tag == 0){
            printf("[Worker %d] Received terminal signal.\n", proc_id);
            break;
        }
        
        std::vector<unsigned int> colOcp, colAvl;
        for (int i = 0; i < n; ++i) {
            if (qPos[i] != n + 1)
                colOcp.push_back(qPos[i]);
        }
        for (int i = 0; i < n; ++i) {
            if (!std::count(colOcp.begin(), colOcp.end(), i))
                colAvl.push_back(i);
        }
        

        std::vector<std::vector<unsigned int>> permutations = findPermutations(colAvl, 0, colAvl.size() - 1);
        std::vector<std::vector<unsigned int>> ans;

        for (int i = 0; i < permutations.size(); ++i) {
            std::vector<unsigned int> tmp;
            int avaCount = 0;
            for (int j = 0; j < n; ++j) {
                if (qPos[j] == n + 1) {
                    tmp.push_back(permutations[i][avaCount]);
                    avaCount++;
                } else
                    tmp.push_back(qPos[j]);
            }
            // printf("The solution is %d\n", isValidSol(tmp));
            

            if (isValidSol(tmp)) {
                // print_vector(tmp);
                ans.push_back(tmp);
            }
        }


        if (exit_on_first) {
            
            unsigned int ret[n];
            if (ans.size() > 0){
                for (int i = 0; i < n; ++i) ret[i] = ans[0][i];
            }
            else
                for (int i = 0; i < n; ++i) ret[i] = n+1;

            int len;
            if (ans.size() > 0) len = 1; 
            else len = 0; 

            MPI_Send(&len, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
            // printf("Got soluton:\n");
            // print_array(ret);
            MPI_Send(&ret, n, MPI_UNSIGNED, 0, 2, MPI_COMM_WORLD);
            // printf("[Worker]Sent one complete solution from %d...\n", proc_id);

        }else{
            unsigned int ret[n * ans.size()];
            for (unsigned int i = 0; i < ans.size(); ++i) {
                for (unsigned int j = 0; j < n; ++j) {
                    ret[i * n + j] = ans[i][j];
                }
            }

            int len = ans.size();
            // printf("Solu len: %d.\n", len);

            MPI_Send(&len, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
            MPI_Send(&ret, len*n, MPI_UNSIGNED, 0, 2, MPI_COMM_WORLD);
        }
    }
}








