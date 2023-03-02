// // functions used for adjusting to steam trap's unique environment
// // Created 1/18/2023

// #include "common.h"

// // =================================================================
// // Function to learn the threshold of wave amplitude which will 
// // determine whether valve is open or closed on any arbitrary steam
// // trap. Method is k-means clustering.
// // =================================================================
// float learnAmplitudeThreshold() {
//     Serial.println("entering function");
//     float centroid0, centroid1;
//     float computed_thresholds[NUM_TUNING_TRIALS];
//     float sample_data[NUM_TUNING_SAMPLES];
//     int cluster_map[NUM_TUNING_SAMPLES]; // ith element belongs to either cluster 0 (closed) or 1 (open)
    
//     // compute a threshold for each trial
//     Serial.printf("number of tuning trials: %f%n", NUM_TUNING_TRIALS);
//     for (int i=0; i<NUM_TUNING_TRIALS; i++) {
//         Serial.printf("TRIAL %f%n", i);
        
//         // blink slow
//         for (int x=0; x<10; x++) {
//             digitalWrite(LED_BUILTIN, HIGH);
//             delay(250);
//             digitalWrite(LED_BUILTIN, LOW);
//             delay(250);
//         }

//         // init centroids
//         centroid0 = 0;
//         centroid1 = MAX_VOLTAGE;

//         // collect sample data
//         for (int j=0; j<NUM_TUNING_SAMPLES; j++) {
//             sample_data[j] = readWaveAmplitude();
//             Serial.printf("wave amplitude: %f%n", sample_data[j]);
//         }

//         // perform cluster assignment iteration until convergence (MAXOUT=100)
//         float new_centroid0, new_centroid1, cluster0_total, cluster1_total;
//         int cluster0_count, cluster1_count;
//         for (int iter=0; iter<100; iter++) {

//             // blink once
//             digitalWrite(LED_BUILTIN, HIGH);
//             delay(500);
//             digitalWrite(LED_BUILTIN, LOW);

//             // assign samples to clusters
//             for (int j=0; j++; j<NUM_TUNING_SAMPLES) {
//                 cluster_map[j] = (centroid0-sample_data[j]) < (centroid1-sample_data[j]) ? 0 : 1;
//             }

//             // compute average of each cluster
//             cluster0_total = cluster1_total = 0;
//             cluster0_count = cluster1_count = 0;
//             for (int j=0; j++; j<NUM_TUNING_SAMPLES) {
//                 if (cluster_map[j]==0) {
//                     cluster0_count++;
//                     cluster0_total+=sample_data[j];
//                 }
//                 else {
//                     cluster1_count++;
//                     cluster1_total+=sample_data[j];
//                 }
//             }

//             if (!cluster0_count) { // centroid0 was too far away
//                 new_centroid0 = (centroid0 + centroid1)/2;
//             }
//             else if (!cluster1_count) { // centroid1 was too far away
//                 new_centroid1 = (centroid0 + centroid1)/2;
//             }
//             else { // otherwise simply calculate average 
//                 new_centroid0 = cluster0_total/(float)cluster0_count;
//                 new_centroid1 = cluster1_total/(float)cluster1_count;
//             }

//             // test for convergence - have either centroids changed?
//             if (new_centroid0==centroid0 && new_centroid1==centroid1) {
//                 break;
//             }

//             // if they have changed, set new centroids and reevaluate sample
//             centroid0 = new_centroid0;
//             centroid1 = new_centroid1;
//         }

//         // compute and save threshold for this trial (ascending order)
//         computed_thresholds[i] = (centroid0 + centroid1)/2.0;
//         Serial.printf("computed threshold is %f%n", computed_thresholds[i]);
//         float tmp;
//         for (int idx=i; idx--; idx>0 && computed_thresholds[idx]<computed_thresholds[idx-1]) {
//             tmp = computed_thresholds[idx-1];
//             computed_thresholds[idx-1] = computed_thresholds[idx];
//             computed_thresholds[idx] = tmp;
//         }

//         // wait for a bit until next trial
//         delay(TRIAL_DELAY*1000);
//     }

//     // blink fast (we're done)
//     for (int x=0; x<100; x++) {
//         digitalWrite(LED_BUILTIN, HIGH);
//         delay(25);
//         digitalWrite(LED_BUILTIN, LOW);
//         delay(25);
//     }

//     // return lazy median threshold
//     Serial.println("exiting function");
//     return computed_thresholds[int(NUM_TUNING_TRIALS/2)];
// }

// float readWaveAmplitude() {
//     float min, max;
//     float curr_val;
//     min = max = (analogRead(MIC)*MAX_VOLTAGE)/4095.0;

//     // find min and max over HISTORY_THRESHOLD number of readings
//     for (int i=0; i<HISTORY_THRESHOLD; i++) {
//         curr_val = (analogRead(MIC)*MAX_VOLTAGE)/4095.0;
//         if (curr_val < min) {
//             min = curr_val;
//         }
//         if (curr_val > max) {
//             max = curr_val;
//         }
//     }

//     // return the amplitude of analog wave
//     return (max - min);
// }