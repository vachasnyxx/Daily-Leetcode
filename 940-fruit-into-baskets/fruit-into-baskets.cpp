class Solution {
public:
    // Function to find the maximum number of fruits we can collect
    // with at most two types of fruits in the baskets.
    int totalFruit(vector<int>& fruits) {
        // Variable to store the maximum number of fruits collected
        int maxlen = 0;

        // Variables to track the last two fruit types and their counts
        int lastfruit = -1, secondlastfruit = -1;

        // Count of current window size and the last fruit streak
        int currcount = 0, lastfruitstreak = 0;

        // Traverse through each fruit in the array
        for (int fruit : fruits) {

            // If current fruit is same as last or second last, increase window
            if (fruit == lastfruit || fruit == secondlastfruit) {
                currcount++;
            } else {
                // Reset window size to size of last fruit streak + 1 (current
                // fruit)
                currcount = lastfruitstreak + 1;
            }

            // Update streak count
            if (fruit == lastfruit) {
                lastfruitstreak++;
            } else {
                lastfruitstreak = 1;
                secondlastfruit = lastfruit;
                lastfruit = fruit;
            }

            // Update the maximum length
            maxlen = max(maxlen, currcount);
        }

        return maxlen;
    }
};