class Solution {
public:
    double Possible(vector<int>& dist, int mid_speed) {
        double time = 0.0;

        int n = dist.size();

        for (int i = 0; i < n - 1; i++) {
            double t = (double)(dist[i] / (double)mid_speed);
            time += ceil(t);
        }
        time += (double)(dist[n - 1] / (double)mid_speed);
        return time;
    }
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int l = 1;
        int r = 1e7;

        int min_speed = -1;

        while (l <= r) {
            int mid_speed = l + (r - l) / 2;

            if (Possible(dist, mid_speed) <= hour) {
                min_speed = mid_speed;
                r = mid_speed - 1;
            } else {
                l = mid_speed + 1;
            }
        }
        return min_speed;
    }
};