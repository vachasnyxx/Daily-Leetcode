class Solution {
public:

    bool possibleHai(vector<int>& time, long long givenTime, int totalTrips){
        long long actualTrips = 0;  // kitna cover ho payega 

        for(int &t: time){
            actualTrips += givenTime/t; // number of trips har bus k
        }

        return actualTrips >= totalTrips;
    }

    long long minimumTime(vector<int>& time, int totalTrips) {
        int n = time.size();

        long long l = 1;
        long long r = (long long) *min_element(begin(time),end(time)) * totalTrips;

        while(l < r){
            long long mid_time = l + (r - l)/2;

            if(possibleHai(time,mid_time,totalTrips)) {
                r = mid_time;
            }
            else{
                l = mid_time +1;
            }
        }
        return l;
    }
};