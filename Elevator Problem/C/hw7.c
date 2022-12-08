// #include"elevator.h"
// #include<unistd.h>
// #include<stdlib.h>
// #include<stdio.h>
// #include<pthread.h>

// pthread_mutex_t passenger_lock;
// pthread_mutex_t elevator_lock;
// pthread_mutex_t scheduling_lock;
// int elevator_direction=1;

// int elevator_floor = 0;
// int is_enter_ready = 0;
// int is_exit_ready = 0;
// int is_passenger_ready = 0;
// pthread_cond_t enter_signal = PTHREAD_COND_INITIALIZER;
// pthread_cond_t exit_signal = PTHREAD_COND_INITIALIZER;
// pthread_cond_t passenger_signal = PTHREAD_COND_INITIALIZER;
// pthread_cond_t ind_signal = PTHREAD_COND_INITIALIZER;
// pthread_cond_t calc_signal = PTHREAD_COND_INITIALIZER;
// pthread_barrier_t all_entered;
// pthread_barrier_t all_exited;


// int number_in = 0;
// int pass_index = 0;
// struct passenger {
//     int start;
//     int end;
//     int elevator;
// } passengers[PASSENGERS];

// struct elev_info {
// 	int floor;
// 	int passengers[MAX_CAPACITY];
//     int index;
// };

// struct floor_info {
// 	int total_enter[PASSENGERS];
//     int enter_index;
//     int total_exit[PASSENGERS];
//     int exit_index;
   
// } floor_infos[FLOORS];

// struct floor_score {
// 	double score;
//     int valid;
   
// } floor_scores[FLOORS];


// struct elev_info elev_one;

// bool done = false;

// int max_floor;

// int count;

// int steps[100];
// int si;

// int start_elev = 0;

// int num_exit = 0;
// int num_enter = 0;


// // // time waste



// bool checkexit(int floor, int bad []) {
//     for (int i = 0; i < FLOORS; i++) {
//         if (bad[i] == floor) {
//             return true;
//         }
//     }
//     return false;
// }

// int findMax(int temp [], int bad []) {
//     int max_floor = 0;
//     int max_score = 0;
//     for (int i = 0; i < FLOORS; i++) {
//         if (temp[i] > max_score && !checkexit(i, bad)) {
//             max_floor = i;
//             max_score = temp[i];
//         }
//     }
//     return max_floor;
// }


// void calculate_to_exit() {
//      for (int i = 0; i < elev_one.index; i++) {
//         if (passengers[elev_one.passengers[i]].end == elev_one.floor) {
//            num_exit++;
//         }
//     }
// }


// bool contains_entry(int passenger) {
//     //log(8,"contes %d", passenger);
//     if (passengers[passenger].elevator != -1) {
//         return false;
//     }
//     for (int i = 0; i < elev_one.index; i++) {
//         if (elev_one.passengers[i] == passenger) {
//            return true;
//         }
//     }
//     return false;
// }


// void calculate_route() {
//     count++;
//     done = true;
//     for (int i = 0; i < FLOORS; i++) {
//         if (!(floor_infos[i].enter_index == 0 && floor_infos[i].exit_index == 0)) {
//             done = false;
//             break;
//         }
//     }

//     if (done) {
//         for (int i = 0; i < si; i++) {
//             log(8,"step %d\n", steps[i]);
//         }
//         log(8,"steps took %d\n", si);
//         return;
//     }
//     double max_score = -2147483648;

//     for (int i = 0; i < FLOORS; i++) {
//         floor_scores[i].score = 0;
//         floor_scores[i].valid = 0;
//     }
   
//     for (int i = 0; i < FLOORS; i++) {
//         log(8,"Floor %d: ", i);
//         for (int j = 0; j < floor_infos[i].enter_index; j++) {
//              log(8,"Enter %d | ", floor_infos[i].total_enter[j]);
//         }
//         for (int j = 0; j < floor_infos[i].exit_index; j++) {
//              log(8,"Exit %d | ", floor_infos[i].total_exit[j]);
//         }
//         log(8,"%d\n", -1);
//     }


//    for (int i = 0; i < FLOORS; i++) {
//         int can_exit = 0;
//          for (int j = 0; j < elev_one.index; j++) {
//             if (passengers[elev_one.passengers[j]].end == i) {
//                 floor_scores[i].score++;
//                 can_exit++;
//                 floor_scores[i].valid = 1;
//             }
//         }

//         int a = MAX_CAPACITY - can_exit - elev_one.index;
//         int b = floor_infos[i].enter_index;

//         if (a > 0 && b > 0) {
//             floor_scores[i].score += (a > b) ? b : a;
//             floor_scores[i].valid = 1;
//         }

//         int temp[FLOORS];
//         for (int k = 0; k < FLOORS; k++) {
//             temp[k] = 0;
//         }
       
//         for (int k = 0; k < elev_one.index; k++) {
//             temp[passengers[elev_one.passengers[k]].end]++;
//         }
//         for (int k = 0; k < floor_infos[i].enter_index; k++) {
//             temp[passengers[floor_infos[i].total_enter[k]].end]++;
//         }


//         //  for (int k = 0; k < FLOORS; k++) {
//         //      //if (temp[k] > 0) {
//         //          log(8,"%d, ", temp[k]);
//         //      //}
           
//         // }
//         // log(8,"%d\n", 0);
      
//        int t [FLOORS];
//        int t_index = 0;
//        int t_max = -1;
//        int tmp_index = floor_infos[i].enter_index;
//        //for (int u = 0; u < 5; u++) {
//        while (1) {
//             //log(8,"why not %d\n", a);
//             if (a == 0 || tmp_index == 0) {
//                 break;
//             }
//             int t_max = findMax(temp, t);
//             t[t_index] = t_max;
//             t_index++;
//             //log(8,"max is  %d\n", t_max);
//             int tot = 0;
//             for (int k = 0; k < floor_infos[i].enter_index; k++) {
//                 if(passengers[floor_infos[i].total_enter[k]].end == t_max) {
//                    tot++;
//                    a--;
//                    tmp_index--;
//                 }
//             }
//             if (tot > 1) {
//                 floor_scores[i].score += 1 * tot;
//             }
            
//         }
       
//         floor_scores[i].score -= (pass_index)*abs(i - max_floor)/(20.0*FLOORS);
//         //log(8,"right now score %d- %f\n", i, floor_scores[i].score);
//     }

//     //floor_scores[max_floor].valid = 0;

//     log(8,"Current Floor %d\n", max_floor);

//     for (int i = 0; i < FLOORS; i++) {
//         if (floor_scores[i].score > max_score && floor_scores[i].valid) {
//            max_score = floor_scores[i].score;
//            max_floor = i;
//         }
//     }

   
   
   
//     elev_one.floor = max_floor;
//     calculate_to_exit();

//     for (int i = 0; i < elev_one.index; i++) {
//          for (int j = 0; j < floor_infos[max_floor].exit_index; j++) {
//            if (elev_one.passengers[i] == floor_infos[max_floor].total_exit[j]) {
//                elev_one.passengers[i] = elev_one.passengers[elev_one.index - 1];
//                elev_one.index--;
//                floor_infos[max_floor].total_exit[j] = floor_infos[max_floor].total_exit[floor_infos[max_floor].exit_index - 1];
//                floor_infos[max_floor].exit_index--;
//                i--;
//                pass_index--;
//            }
//         }
//     }




//     int temp[FLOORS];
//     for (int k = 0; k < FLOORS; k++) {
//         temp[k] = 0;
//     }
//     for (int k = 0; k < elev_one.index; k++) {
//         temp[passengers[elev_one.passengers[k]].end]++;
//     }
//     for (int k = 0; k < floor_infos[max_floor].enter_index; k++) {
//         temp[passengers[floor_infos[max_floor].total_enter[k]].end]++;
//     }

//     int t [FLOORS];
//     int t_index = 0;
//     int t_max = -1;
//     int tmp_index = floor_infos[max_floor].enter_index;


//     int old_index = elev_one.index;
   
//     // for (int i = 0; i < floor_infos[max_floor].enter_index; i++) {
//     //     if (elev_one.index >= MAX_CAPACITY) {
//     //         break;
//     //     }

        
//     while (1) {
//         if (elev_one.index >= MAX_CAPACITY || floor_infos[max_floor].enter_index == 0) {
//             break;
//         }
//         int t_max = findMax(temp, t);
//         t[t_index] = t_max;
//         t_index++;
//         int tot = 0;
//         for (int i = 0; i < floor_infos[max_floor].enter_index && elev_one.index < MAX_CAPACITY; i++) {
//             if(passengers[floor_infos[max_floor].total_enter[i]].end == t_max) {
//                 elev_one.passengers[elev_one.index] = floor_infos[max_floor].total_enter[i];
//                 elev_one.index++;
//                 floor_infos[max_floor].total_enter[i] = floor_infos[max_floor].total_enter[floor_infos[max_floor].enter_index - 1];
//                 floor_infos[max_floor].enter_index--;
//                 i--;
//                 pass_index--;

//                 tot++;
//                 tmp_index--;
//             }
//         }



//         // wait
       
       
//     }


//     if ((elev_one.index - old_index)  > 0) {
//         num_enter =  elev_one.index - old_index;
//     } else {
//         num_enter =  0;
//     }

   
//     log(8,"Max Score %f\n", max_score);
//     log(8,"Max Floor %d\n", max_floor);
//     log(8,"Real Floor %d\n", elev_one.floor);

//     for (int i = 0; i < FLOORS; i++) {
//         if (floor_scores[i].valid) {
//             log(8,"Score %d: %f\n", i, floor_scores[i].score);
//         }
//     }

//     for (int i = 0; i < elev_one.index; i++) {
//         log(8,"current pass %d\n", elev_one.passengers[i]);
//     }
//     steps[si] = max_floor;
//     si++;
//     log(8,"left %d, %d\n\n\n", pass_index, count);
   
     
//     calculate_route();
//     start_elev = 1;
//     pthread_cond_signal(&calc_signal);
// }


// void scheduler_init() {
//     pthread_mutex_init(&passenger_lock,0);
//     pthread_mutex_init(&elevator_lock,0);
//     pthread_mutex_init(&scheduling_lock, 0);
//     pthread_mutex_lock(&elevator_lock);

//     elev_one.index = 0;
//     max_floor = 0;
//     count = 0;
//     si = 0;
// }

// void passenger_request(int passenger, int from_floor, int to_floor, void (*enter)(int, int), void(*exit)(int, int)) {
//     pthread_mutex_lock(&scheduling_lock);
//     passengers[passenger].start = from_floor;
//     passengers[passenger].end = to_floor;
//     passengers[passenger].elevator = -1;
//     pass_index++;

//     if (pass_index == PASSENGERS) {
//         for (int i = 0; i < PASSENGERS; i++) {
//            log(8,"Karan %d %d %d %d\n", i, passengers[i].start, passengers[i].end, passengers[i].elevator);
//         }
//         for (int i = 0; i < PASSENGERS; i++) {
//             if (passengers[i].elevator == -1) {
//                 floor_infos[passengers[i].start].total_enter[floor_infos[passengers[i].start].enter_index] = i;
//                 floor_infos[passengers[i].start].enter_index++;
//                 floor_infos[passengers[i].end].total_exit[floor_infos[passengers[i].end].exit_index] = i;
//                 floor_infos[passengers[i].end].exit_index++;
//             }
//         }
//        pass_index = pass_index * 2;
//        calculate_route();
//     }

//     pthread_mutex_unlock(&scheduling_lock);



//     //pthread_mutex_lock(&passenger_lock);
//     pthread_mutex_lock(&elevator_lock);
   
//     while(!(is_enter_ready && contains_entry(passenger))) {
//         //pthread_mutex_unlock(&passenger_lock); 
//         pthread_cond_wait(&enter_signal, &elevator_lock);
//     }

//     //  while(!(is_enter_ready && contains_entry(passenger))) {
//     //     //pthread_mutex_unlock(&passenger_lock);
//     //     pthread_mutex_unlock(&elevator_lock);
//     //     pthread_mutex_lock(&elevator_lock);
//     // }

//     log(8,"enter signal %d, %d\n", passenger, is_enter_ready);
//     //pthread_mutex_lock(&passenger_lock);
//     //is_elevator_ready = 0;

//     //enter the lift
//     passengers[passenger].elevator = 0;
//     enter(passenger, 0);
    

//     pthread_mutex_unlock(&elevator_lock);
//     pthread_cond_broadcast(&enter_signal);
//     pthread_barrier_wait(&all_entered);
   



   
//     while(!(is_exit_ready && elev_one.floor == to_floor)) {
//         pthread_cond_wait(&exit_signal, &elevator_lock);
//     }

   
//     log(8,"is it %d\n", is_exit_ready);
//     exit(passenger,0);
//     //is_passenger_ready = 1;
    
//     pthread_mutex_unlock(&elevator_lock);
//     pthread_cond_broadcast(&exit_signal);
   
//     pthread_barrier_wait(&all_exited);

//     // //pthread_mutex_unlock(&passenger_lock);
// }

// void elevator_ready(int elevator, int at_floor, void(*move_direction)(int, int), void(*door_open)(int), void(*door_close)(int)) {
//     while (1) {

//     }
//     if(elevator == 0) {
//         pthread_mutex_lock(&scheduling_lock);
//         while (!start_elev) {
//             pthread_cond_wait(&calc_signal, &scheduling_lock);
//         }
//         pthread_mutex_unlock(&scheduling_lock);
//         if (elev_one.floor == at_floor) {
           
//             door_open(elevator);
//             pthread_barrier_init(&all_exited, 0, num_exit + 1);
//             pthread_barrier_init(&all_entered, 0, num_enter + 1);
//             log(8,"to exit %d\n", num_exit);
//             log(8,"to enter %d\n", num_enter);
//             is_exit_ready = 1;
//             pthread_mutex_unlock(&elevator_lock);
//             pthread_cond_broadcast(&exit_signal);
//             pthread_barrier_wait(&all_exited);
//             log(8,"done waiting %d\n", number_in);
            


//             // while(!is_passenger_ready) {
//             //    /* WAIT FOR CONDITION HERE */
//             //    pthread_cond_wait(&passenger_signal, &elevator_lock);
//             // }


//             pthread_mutex_lock(&elevator_lock);
//             is_exit_ready = 0;
//             is_enter_ready = 1;
//             pthread_mutex_unlock(&elevator_lock);
//             pthread_cond_broadcast(&enter_signal);
           
           
           
//             // while(!is_passenger_ready) {
//             //    /* WAIT FOR CONDITION HERE */
//             //    pthread_cond_wait(&passenger_signal, &elevator_lock);
//             // }
           
//             pthread_barrier_wait(&all_entered);
//             log(8,"done waiting2 %d\n", number_in);
//             pthread_mutex_lock(&elevator_lock);
//             is_enter_ready = 0;
//             //is_passenger_ready = 0;
//             door_close(elevator);
//             start_elev = 0;
//             num_exit = 0;
//             pthread_mutex_lock(&scheduling_lock);
//             calculate_route();
//             pthread_mutex_unlock(&scheduling_lock);
//         }
//         //pthread_mutex_lock(&elevator_lock);
//         if (elev_one.floor > at_floor) {
//             elevator_direction = 1;
//         } else {
//             elevator_direction = -1;
//         }
//         move_direction(elevator,elevator_direction);
//         elevator_floor = at_floor+elevator_direction;
//     }
// }




// // look over here


// #include"elevator.h"
// #include<unistd.h>
// #include<stdlib.h>
// #include<stdio.h>
// #include<pthread.h>

// pthread_mutex_t passenger_lock;
// pthread_mutex_t elevator_lock;
// pthread_mutex_t scheduling_lock;
// int elevator_direction=1;

// int elevator_floor = 0;
// int is_enter_ready = 0;
// int is_exit_ready = 0;
// int is_passenger_ready = 0;
// pthread_cond_t enter_signal = PTHREAD_COND_INITIALIZER;
// pthread_cond_t exit_signal = PTHREAD_COND_INITIALIZER;
// pthread_cond_t passenger_signal = PTHREAD_COND_INITIALIZER;
// pthread_cond_t ind_signal = PTHREAD_COND_INITIALIZER;
// pthread_cond_t calc_signal = PTHREAD_COND_INITIALIZER;
// pthread_barrier_t all_entered;
// pthread_barrier_t all_exited;


// int number_in = 0;
// int pass_index = 0;
// struct passenger {
//     int start;
//     int end;
//     int elevator;
// } passengers[PASSENGERS];

// struct elev_info {
// 	int floor;
// 	int passengers[MAX_CAPACITY];
//     int index;
// };

// struct floor_info {
// 	int total_enter[PASSENGERS];
//     int enter_index;
//     int total_exit[PASSENGERS];
//     int exit_index;
   
// } floor_infos[FLOORS];

// struct floor_score {
// 	double score;
//     int valid;
   
// } floor_scores[FLOORS];


// struct elev_info elev_one;

// bool done = false;

// int max_floor;

// int count;

// int steps[100];
// int si;

// int start_elev = 0;

// int num_exit = 0;
// int num_enter = 0;


// // // time waste


// void calculate_to_exit() {
//      for (int i = 0; i < elev_one.index; i++) {
//         if (passengers[elev_one.passengers[i]].end == elev_one.floor) {
//            num_exit++;
//         }
//     }
// }


// bool contains_entry(int passenger) {
//     //log(8,"contes %d", passenger);
//     if (passengers[passenger].elevator != -1) {
//         return false;
//     }
//     for (int i = 0; i < elev_one.index; i++) {
//         if (elev_one.passengers[i] == passenger) {
//            return true;
//         }
//     }
//     return false;
// }


// void calculate_route() {
//     count++;
//     done = true;
//     for (int i = 0; i < FLOORS; i++) {
//         if (!(floor_infos[i].enter_index == 0 && floor_infos[i].exit_index == 0)) {
//             done = false;
//             break;
//         }
//     }

//     if (done) {
//         for (int i = 0; i < si; i++) {
//             log(8,"step %d\n", steps[i]);
//         }
//          log(8,"took steps %d\n", si);
//         return;
//     }
//     double max_score = -2147483648;

//     for (int i = 0; i < FLOORS; i++) {
//         floor_scores[i].score = 0;
//         floor_scores[i].valid = 0;
//     }
   
//     for (int i = 0; i < FLOORS; i++) {
//         log(8,"Floor %d: ", i);
//         for (int j = 0; j < floor_infos[i].enter_index; j++) {
//              log(8,"Enter %d | ", floor_infos[i].total_enter[j]);
//         }
//         for (int j = 0; j < floor_infos[i].exit_index; j++) {
//              log(8,"Exit %d | ", floor_infos[i].total_exit[j]);
//         }
//         log(8,"%d\n", -1);
//     }


//    for (int i = 0; i < FLOORS; i++) {
//         int can_exit = 0;
//          for (int j = 0; j < elev_one.index; j++) {
//             if (passengers[elev_one.passengers[j]].end == i) {
//                 floor_scores[i].score++;
//                 can_exit++;
//                 floor_scores[i].valid = 1;
//             }
//         }

//         int a = MAX_CAPACITY - can_exit - elev_one.index;
//         int b = floor_infos[i].enter_index;
//         if (a > 0 && b > 0) {
//             floor_scores[i].score += (a > b) ? b : a;
//             floor_scores[i].valid = 1;
//         }
       
//         floor_scores[i].score -= (pass_index)*abs(i - max_floor)/(20.0*FLOORS);
//     }
//     floor_scores[max_floor].valid = 0;

//     log(8,"Current Floor %d\n", max_floor);

//     for (int i = 0; i < FLOORS; i++) {
//         if (floor_scores[i].score > max_score && floor_scores[i].valid) {
//            max_score = floor_scores[i].score;
//            max_floor = i;
//         }
//     }

   
   
   
//     elev_one.floor = max_floor;
//     calculate_to_exit();

//     for (int i = 0; i < elev_one.index; i++) {
//          for (int j = 0; j < floor_infos[max_floor].exit_index; j++) {
//            if (elev_one.passengers[i] == floor_infos[max_floor].total_exit[j]) {
//                elev_one.passengers[i] = elev_one.passengers[elev_one.index - 1];
//                elev_one.index--;
//                floor_infos[max_floor].total_exit[j] = floor_infos[max_floor].total_exit[floor_infos[max_floor].exit_index - 1];
//                floor_infos[max_floor].exit_index--;
//                i--;
//                pass_index--;
//            }
//         }
//     }

//     int old_index = elev_one.index;
   

//     for (int i = 0; i < floor_infos[max_floor].enter_index; i++) {
//         if (elev_one.index >= MAX_CAPACITY) {
//             break;
//         }
//         elev_one.passengers[elev_one.index] = floor_infos[max_floor].total_enter[i];
//         elev_one.index++;
//         floor_infos[max_floor].total_enter[i] = floor_infos[max_floor].total_enter[floor_infos[max_floor].enter_index - 1];
//         floor_infos[max_floor].enter_index--;
//         i--;
//         pass_index--;
       
//     }


//     if ((elev_one.index - old_index)  > 0) {
//         num_enter =  elev_one.index - old_index;
//     } else {
//         num_enter =  0;
//     }

   
//     log(8,"Max Score %f\n", max_score);
//     log(8,"Max Floor %d\n", max_floor);
//     log(8,"Real Floor %d\n", elev_one.floor);

//     for (int i = 0; i < FLOORS; i++) {
//         if (floor_scores[i].valid) {
//             log(8,"Score %d: %f\n", i, floor_scores[i].score);
//         }
//     }

//     for (int i = 0; i < elev_one.index; i++) {
//         log(8,"current pass %d\n", elev_one.passengers[i]);
//     }
//     steps[si] = max_floor;
//     si++;
//     log(8,"left %d, %d\n\n\n", pass_index, count);
   
     
//     calculate_route();
//     start_elev = 1;
//     pthread_cond_signal(&calc_signal);
// }


// void scheduler_init() {
//     pthread_mutex_init(&passenger_lock,0);
//     pthread_mutex_init(&elevator_lock,0);
//     pthread_mutex_init(&scheduling_lock, 0);
//     pthread_mutex_lock(&elevator_lock);

//     elev_one.index = 0;
//     max_floor = 0;
//     count = 0;
//     si = 0;
// }

// void passenger_request(int passenger, int from_floor, int to_floor, void (*enter)(int, int), void(*exit)(int, int)) {
//     pthread_mutex_lock(&scheduling_lock);
//     passengers[passenger].start = from_floor;
//     passengers[passenger].end = to_floor;
//     passengers[passenger].elevator = -1;
//     pass_index++;

//     if (pass_index == PASSENGERS) {
//         for (int i = 0; i < PASSENGERS; i++) {
//            log(8,"Karan %d %d %d %d\n", i, passengers[i].start, passengers[i].end, passengers[i].elevator);
//         }
//         for (int i = 0; i < PASSENGERS; i++) {
//             if (passengers[i].elevator == -1) {
//                 floor_infos[passengers[i].start].total_enter[floor_infos[passengers[i].start].enter_index] = i;
//                 floor_infos[passengers[i].start].enter_index++;
//                 floor_infos[passengers[i].end].total_exit[floor_infos[passengers[i].end].exit_index] = i;
//                 floor_infos[passengers[i].end].exit_index++;
//             }
//         }
//        pass_index = pass_index * 2;
//        calculate_route();
//     }

//     pthread_mutex_unlock(&scheduling_lock);



//     //pthread_mutex_lock(&passenger_lock);
//     pthread_mutex_lock(&elevator_lock);
   
//     while(!(is_enter_ready && contains_entry(passenger))) {
//         //pthread_mutex_unlock(&passenger_lock); 
//         pthread_cond_wait(&enter_signal, &elevator_lock);
//     }

//     //  while(!(is_enter_ready && contains_entry(passenger))) {
//     //     //pthread_mutex_unlock(&passenger_lock);
//     //     pthread_mutex_unlock(&elevator_lock);
//     //     pthread_mutex_lock(&elevator_lock);
//     // }

//     log(8,"enter signal %d, %d\n", passenger, is_enter_ready);
//     //pthread_mutex_lock(&passenger_lock);
//     //is_elevator_ready = 0;

//     //enter the lift
//     passengers[passenger].elevator = 0;
//     enter(passenger, 0);
    

//     pthread_mutex_unlock(&elevator_lock);
//     pthread_cond_broadcast(&enter_signal);
//     pthread_barrier_wait(&all_entered);
   



   
//     while(!(is_exit_ready && elev_one.floor == to_floor)) {
//         pthread_cond_wait(&exit_signal, &elevator_lock);
//     }

   
//     log(8,"is it %d\n", is_exit_ready);
//     exit(passenger,0);
//     //is_passenger_ready = 1;
    
//     pthread_mutex_unlock(&elevator_lock);
//     pthread_cond_broadcast(&exit_signal);
   
//     pthread_barrier_wait(&all_exited);

//     // //pthread_mutex_unlock(&passenger_lock);
// }

// void elevator_ready(int elevator, int at_floor, void(*move_direction)(int, int), void(*door_open)(int), void(*door_close)(int)) {
   
//    while (1) {

//    }
//     if(elevator == 0) {
//         pthread_mutex_lock(&scheduling_lock);
//         while (!start_elev) {
//             pthread_cond_wait(&calc_signal, &scheduling_lock);
//         }
//         pthread_mutex_unlock(&scheduling_lock);
//         if (elev_one.floor == at_floor) {
           
//             door_open(elevator);
//             pthread_barrier_init(&all_exited, 0, num_exit + 1);
//             pthread_barrier_init(&all_entered, 0, num_enter + 1);
//             log(8,"to exit %d\n", num_exit);
//             log(8,"to enter %d\n", num_enter);
//             is_exit_ready = 1;
//             pthread_mutex_unlock(&elevator_lock);
//             pthread_cond_broadcast(&exit_signal);
//             pthread_barrier_wait(&all_exited);
//             log(8,"done waiting %d\n", number_in);
            


//             // while(!is_passenger_ready) {
//             //    /* WAIT FOR CONDITION HERE */
//             //    pthread_cond_wait(&passenger_signal, &elevator_lock);
//             // }


//             pthread_mutex_lock(&elevator_lock);
//             is_exit_ready = 0;
//             is_enter_ready = 1;
//             pthread_mutex_unlock(&elevator_lock);
//             pthread_cond_broadcast(&enter_signal);
           
           
           
//             // while(!is_passenger_ready) {
//             //    /* WAIT FOR CONDITION HERE */
//             //    pthread_cond_wait(&passenger_signal, &elevator_lock);
//             // }
           
//             pthread_barrier_wait(&all_entered);
//             log(8,"done waiting2 %d\n", number_in);
//             pthread_mutex_lock(&elevator_lock);
//             is_enter_ready = 0;
//             //is_passenger_ready = 0;
//             door_close(elevator);
//             start_elev = 0;
//             num_exit = 0;
//             pthread_mutex_lock(&scheduling_lock);
//             calculate_route();
//             pthread_mutex_unlock(&scheduling_lock);
//         }
//         //pthread_mutex_lock(&elevator_lock);
//         if (elev_one.floor > at_floor) {
//             elevator_direction = 1;
//         } else {
//             elevator_direction = -1;
//         }
//         move_direction(elevator,elevator_direction);
//         elevator_floor = at_floor+elevator_direction;
//     }
// }




// look here


#include"elevator.h"
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

pthread_mutex_t passenger_lock;
pthread_mutex_t elevator_lock;
pthread_mutex_t scheduling_lock;

//int elevator_direction=1;


pthread_cond_t enter_signal = PTHREAD_COND_INITIALIZER;
pthread_cond_t exit_signal = PTHREAD_COND_INITIALIZER;
pthread_cond_t passenger_signal = PTHREAD_COND_INITIALIZER;
pthread_cond_t calc_signal = PTHREAD_COND_INITIALIZER;

// pthread_barrier_t all_entered;
// pthread_barrier_t all_exited;


pthread_barrier_t all_done;

int pass_index = 0;
struct passenger {
    int start;
    int end;
    int elevator;
} passengers[PASSENGERS];


struct elev_info {
	int floor;
	int passengers[MAX_CAPACITY];
    int index;
    int num_exit;
    int num_enter;
    int is_enter_ready;
    int is_exit_ready;
    int calc_again;
    int prev_floor;
    pthread_barrier_t all_entered;
    pthread_barrier_t all_exited;

} elev_infos[ELEVATORS];

struct floor_info {
	int total_enter[PASSENGERS];
    int enter_index;
    int total_exit[PASSENGERS];
    int exit_index;
   
} floor_infos[FLOORS];

struct floor_score {
	double score;
    int valid;
   
} floor_scores[FLOORS];



// per???


// per

// per???
int start_elev = 0;








void calculate_to_exit(int elevator) {
     for (int i = 0; i < elev_infos[elevator].index; i++) {
        if (passengers[elev_infos[elevator].passengers[i]].end == elev_infos[elevator].floor) {
           elev_infos[elevator].num_exit++;
        }
    }
}


void calculate_route(int elevator) {
    log(8,"calculating %d\n", 1);
  

    int max_floor = 0;
    double max_score = -2147483648;

    for (int i = 0; i < FLOORS; i++) {
        floor_scores[i].score = 0;
        floor_scores[i].valid = 0;
    }
   
    // for (int i = 0; i < FLOORS; i++) {
    //     log(8,"Floor %d: ", i);
    //     for (int j = 0; j < floor_infos[i].enter_index; j++) {
    //          log(8,"Enter %d | ", floor_infos[i].total_enter[j]);
    //     }
    //     for (int j = 0; j < floor_infos[i].exit_index; j++) {
    //          log(8,"Exit %d | ", floor_infos[i].total_exit[j]);
    //     }
    //     log(8,"%d\n", -1);
    // }


   for (int i = 0; i < FLOORS; i++) {
        int can_exit = 0;
         for (int j = 0; j < elev_infos[elevator].index; j++) {
            if (passengers[elev_infos[elevator].passengers[j]].end == i) {
                floor_scores[i].score++;
                can_exit++;
                floor_scores[i].valid = 1;
            }
        }

        int a = MAX_CAPACITY - can_exit - elev_infos[elevator].index;
        int b = floor_infos[i].enter_index;
        if (a > 0 && b > 0) {
            floor_scores[i].score += (a > b) ? b : a;
            floor_scores[i].valid = 1;
        }
       
        floor_scores[i].score -= (pass_index)*abs(i - elev_infos[elevator].prev_floor)/(20.0*FLOORS);
    }
    floor_scores[elev_infos[elevator].prev_floor].valid = 0;

    //log(8,"Current Floor %d\n", max_floor);

    for (int i = 0; i < FLOORS; i++) {
        if (floor_scores[i].score > max_score && floor_scores[i].valid) {
           max_score = floor_scores[i].score;
           max_floor = i;
        }
    }

   
   
   
    elev_infos[elevator].floor = max_floor;
    if (elev_infos[elevator].floor != max_floor) {
        log(8,"boom %d\n", 1);
    }
    calculate_to_exit(elevator);

    for (int i = 0; i < elev_infos[elevator].index; i++) {
         for (int j = 0; j < floor_infos[max_floor].exit_index; j++) {
           if (elev_infos[elevator].passengers[i] == floor_infos[max_floor].total_exit[j]) {
               elev_infos[elevator].passengers[i] = elev_infos[elevator].passengers[elev_infos[elevator].index - 1];
               elev_infos[elevator].index--;
               floor_infos[max_floor].total_exit[j] = floor_infos[max_floor].total_exit[floor_infos[max_floor].exit_index - 1];
               floor_infos[max_floor].exit_index--;
               i--;
               pass_index--;
           }
        }
    }

    int old_index = elev_infos[elevator].index;
   

    for (int i = 0; i < floor_infos[max_floor].enter_index; i++) {
        if (elev_infos[elevator].index >= MAX_CAPACITY) {
            break;
        }
        elev_infos[elevator].passengers[elev_infos[elevator].index] = floor_infos[max_floor].total_enter[i];
        passengers[floor_infos[max_floor].total_enter[i]].elevator = elevator;
        elev_infos[elevator].index++;
        floor_infos[max_floor].total_enter[i] = floor_infos[max_floor].total_enter[floor_infos[max_floor].enter_index - 1];
        floor_infos[max_floor].enter_index--;
        i--;
        pass_index--;
       
    }


    if ((elev_infos[elevator].index - old_index)  > 0) {
        elev_infos[elevator].num_enter =  elev_infos[elevator].index - old_index;
    } else {
        elev_infos[elevator].num_enter =  0;
    }

   
    log(8,"Max Score %f\n", max_score);
    log(8,"Max Floor %d\n", max_floor);
    log(8,"Real Floor %d, %d\n", elevator, elev_infos[elevator].floor);
    log(8,"Current Floor %d\n",elev_infos[elevator].prev_floor);

    // for (int i = 0; i < FLOORS; i++) {
    //     if (floor_scores[i].valid) {
    //         log(8,"Score %d: %f\n", i, floor_scores[i].score);
    //     }
    // }

    for (int i = 0; i < elev_infos[elevator].index; i++) {
        log(8,"current pass %d\n", elev_infos[elevator].passengers[i]);
    }
   
     
    //calculate_route();

    for (int i = 0; i < PASSENGERS; i++) {
        //log(8,"Karan %d %d %d %d\n", i, passengers[i].start, passengers[i].end, passengers[i].elevator);
    }

    log(8,"left %d\n\n\n", pass_index);
    elev_infos[elevator].prev_floor = max_floor;
    start_elev = 1;
    pthread_cond_broadcast(&calc_signal);
}


void scheduler_init() {
    pthread_mutex_init(&passenger_lock,0);
    pthread_mutex_init(&elevator_lock,0);
    pthread_mutex_init(&scheduling_lock, 0);
    pthread_mutex_lock(&elevator_lock);
    pthread_barrier_init(&all_done, 0, ELEVATORS);

    for (int i = 0; i < ELEVATORS; i++) {
        elev_infos[i].calc_again = 1;
        elev_infos[i].floor = -1;
    }
}

void passenger_request(int passenger, int from_floor, int to_floor, void (*enter)(int, int), void(*exit)(int, int)) {
    //pthread_mutex_lock(&scheduling_lock);
    passengers[passenger].start = from_floor;
    passengers[passenger].end = to_floor;
    passengers[passenger].elevator = -1;
    pass_index++;

    if (pass_index == PASSENGERS) {
        for (int i = 0; i < PASSENGERS; i++) {
            log(8,"Karan %d %d %d %d\n", i, passengers[i].start, passengers[i].end, passengers[i].elevator);
        }
        for (int i = 0; i < PASSENGERS; i++) {
            floor_infos[passengers[i].start].total_enter[floor_infos[passengers[i].start].enter_index] = i;
            floor_infos[passengers[i].start].enter_index++;
            floor_infos[passengers[i].end].total_exit[floor_infos[passengers[i].end].exit_index] = i;
            floor_infos[passengers[i].end].exit_index++;
        }
       pass_index = pass_index * 2;
       start_elev = 1;
       pthread_cond_signal(&calc_signal);
       //calculate_route();
    }

    //pthread_mutex_unlock(&scheduling_lock);


    //pthread_mutex_lock(&passenger_lock);
    pthread_mutex_lock(&scheduling_lock);
   
    while(!(passengers[passenger].elevator != -1 && elev_infos[passengers[passenger].elevator].is_enter_ready)) {
        //pthread_mutex_unlock(&passenger_lock); 
        pthread_cond_wait(&enter_signal, &scheduling_lock);
    }

    log(8,"enter signal %d\n", passenger);
    //pthread_mutex_lock(&passenger_lock);

    //enter the lift
    //passengers[passenger].elevator = 0;
    pthread_mutex_unlock(&scheduling_lock);
    enter(passenger, passengers[passenger].elevator);
    

   
    pthread_cond_broadcast(&enter_signal);
    pthread_barrier_wait(&elev_infos[passengers[passenger].elevator].all_entered);
   
    pthread_mutex_lock(&scheduling_lock);
    while(!(elev_infos[passengers[passenger].elevator].is_exit_ready && elev_infos[passengers[passenger].elevator].floor == to_floor)) {
        pthread_cond_wait(&exit_signal, &scheduling_lock);
    }

   
    log(8,"is it %d\n", elev_infos[passengers[passenger].elevator].is_exit_ready);
    exit(passenger, passengers[passenger].elevator);
    
    pthread_mutex_unlock(&scheduling_lock);
    pthread_cond_broadcast(&exit_signal);
   
    pthread_barrier_wait(&elev_infos[passengers[passenger].elevator].all_exited);

    // //pthread_mutex_unlock(&passenger_lock);
}

void elevator_ready(int elevator, int at_floor, void(*move_direction)(int, int), void(*door_open)(int), void(*door_close)(int)) {
  
    //if(elevator == 1) {
        
        log(8,"to enter %d, %d\n", elevator, elev_infos[elevator].num_enter);
        // while (!start_elev) {
        //     pthread_cond_wait(&calc_signal, &elevator_lock);
        // }

        if (elev_infos[elevator].floor == at_floor) {
            door_open(elevator);
            pthread_barrier_init(&elev_infos[elevator].all_exited, 0, elev_infos[elevator].num_exit + 1);
            pthread_barrier_init(&elev_infos[elevator].all_entered, 0, elev_infos[elevator].num_enter + 1);
            log(8,"to exit %d, %d\n", elevator, elev_infos[elevator].num_exit);
            log(8,"to enter %d, %d\n", elevator, elev_infos[elevator].num_enter);
            elev_infos[elevator].is_exit_ready = 1;
            //pthread_mutex_unlock(&elevator_lock);
            pthread_cond_broadcast(&exit_signal);
            pthread_barrier_wait(&elev_infos[elevator].all_exited);

            //pthread_mutex_lock(&elevator_lock);
            elev_infos[elevator].is_exit_ready = 0;
            elev_infos[elevator].is_enter_ready = 1;
            //pthread_mutex_unlock(&elevator_lock);
            pthread_cond_broadcast(&enter_signal);
           
           
           
            pthread_barrier_wait(&elev_infos[elevator].all_entered);
            //pthread_mutex_lock(&elevator_lock);
            elev_infos[elevator].is_enter_ready = 0;
            door_close(elevator);
            //start_elev = 0;
            elev_infos[elevator].num_exit = 0;
            elev_infos[elevator].calc_again = 1;
        }
        //pthread_mutex_lock(&scheduling_lock);
        if (elev_infos[elevator].calc_again) {
            elev_infos[elevator].calc_again = 0;
            log(8,"try1 %d\n", elevator);
            //pthread_barrier_wait(&all_done);
            log(8,"try2 %d\n", elevator);
            pthread_mutex_lock(&scheduling_lock);
            calculate_route(elevator);
            pthread_mutex_unlock(&scheduling_lock);
        }
        int elevator_direction = 1;
        if (elev_infos[elevator].floor > at_floor) {
            elevator_direction = 1;
        } else if (elev_infos[elevator].floor < at_floor) {
            elevator_direction = -1;
        }
        move_direction(elevator,elevator_direction);
    //}
}




