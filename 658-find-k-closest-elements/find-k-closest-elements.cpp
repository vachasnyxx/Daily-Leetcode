// Raghav sirs code
// class Solution {
// public:
//     vector<int> findClosestElements(vector<int>& arr, int k, int x) {
//         // S.C = O(K)
//         // T.C = O(logn + KlogK)
//         int n = arr.size();
//         vector<int> ans(k); // k elements insert larenge
//         if (x < arr[0]) {
//             for (int i = 0; i < k; i++) {
//                 ans[i] = arr[i];
//             }
//             return ans;
//         }

//         if (x > arr[n - 1]) {
//             int i = n - 1;
//             int j = k - 1;
//             while (j >= 0) {
//                 ans[j] = arr[i];
//                 j--;
//                 i--;
//             }
//             return ans;
//         }
//         int low = 0;
//         int high = n - 1;
//         bool flag = false; // if x is present in arr or not
//         int t = 0;         // ans arr mein traverse krne ke liye t use kr lenge
//         int mid = -1;
//         // binary search
//         while (low <= high) {
//             mid = low + (high - low) / 2;
//             if (arr[mid] == x) {
//                 flag = true; // present
//                 ans[t] = arr[mid];
//                 t++;
//                 break;
//             } else if (arr[mid] > x) {
//                 high = mid - 1;
//             } else
//                 low = mid + 1;
//         }

//         int lb = high; // lower bound
//         int ub = low;  // upper bound
//         if (flag == true) {
//             lb = mid - 1;
//             ub = mid + 1;
//         }
//         while (t < k && lb >= 0 && ub <= n - 1) {
//             int d1 = abs(x - arr[lb]);
//             int d2 = abs(x - arr[ub]);
//             if (d1 <= d2) {
//                 ans[t] = arr[lb];
//                 // t++; isko bahar likh denge cuz ye dono if and else mein chal
//                 // rha hai
//                 lb--;
//             } else //(d1 <= d2)
//             {
//                 ans[t] = arr[ub];
//                 // t++; isko bahar likh denge cuz ye dono if and else mein chal
//                 // rha hai
//                 ub++;
//             }
//             t++;
//         }
//         if (lb < 0) {
//             while (t < k) {
//                 ans[t] = arr[ub];
//                 ub++;
//                 t++;
//             }
//         }
//         if (ub > n-1) {
//             while (t < k) {
//                 ans[t] = arr[lb];
//                 lb--;
//                 t++;
//             }
//         }
//         sort(ans.begin(), ans.end());   // WORST CASE MEIN = O(KlogK)
//         return ans;
//     }
// };






// class Solution {
// public:
//     vector<int> findClosestElements(vector<int>& arr, int k, int x) {
//         int n = arr.size();
//         vector<int> ans;

//         // Case 1: x smaller than all elements
//         if (x <= arr[0]) {
//             for (int i = 0; i < k; i++) ans.push_back(arr[i]);
//             return ans;
//         }

//         // Case 2: x larger than all elements
//         if (x >= arr[n - 1]) {
//             for (int i = n - k; i < n; i++) ans.push_back(arr[i]);
//             return ans;
//         }

//         // Binary search to find closest position
//         int low = 0, high = n - 1;
//         while (low <= high) {
//             int mid = low + (high - low) / 2;
//             if (arr[mid] < x) low = mid + 1;
//             else high = mid - 1;
//         }

//         // Two pointers around x
//         int lb = high;   // left side
//         int ub = low;    // right side

//         while (ans.size() < k) {
//             if (lb < 0) {
//                 ans.push_back(arr[ub++]);
//             } else if (ub >= n) {
//                 ans.push_back(arr[lb--]);
//             } else {
//                 int d1 = abs(arr[lb] - x);
//                 int d2 = abs(arr[ub] - x);
//                 if (d1 <= d2) ans.push_back(arr[lb--]);
//                 else ans.push_back(arr[ub++]);
//             }
//         }

//         sort(ans.begin(), ans.end());  // ensure ascending order
//         return ans;
//     }
// };





// ============================================================
// LEETCODE 658 - FIND K CLOSEST ELEMENTS
// Pattern: Binary Search (to anchor) + Two-Pointer Expansion
// ============================================================
//
// PLAIN ENGLISH DEFINITION:
// Given a sorted array, find the k elements closest to a value x.
// If there's a tie in distance, prefer the smaller number. Return
// the result sorted in ascending order.
//
// THE ANALOGY (for permanent memory):
// Imagine x is a person standing at a specific spot in a sorted
// line of people (by height, say). You want to pick the k people
// standing CLOSEST to that spot. So you first walk to roughly
// where x would stand in the line (binary search anchors you
// there), then you look one step LEFT and one step RIGHT. Whoever
// is closer to you gets picked into your group first — like a tug
// of war where the closer side always wins the next pick. You keep
// doing this, alternating sides based on who's closer, until your
// group has exactly k people.
//
// WHY THIS BEATS A NAIVE SCAN:
// A naive approach would compute distance for all n elements and
// sort — O(n log n). Here, binary search gets you to the right
// neighborhood in O(log n), and then you only ever touch k elements
// during expansion, making the dominant cost O(log n + k), with a
// final O(k log k) sort of just the small answer array.
// ============================================================

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // Time Complexity  = O(log n + k log k)
        // Space Complexity = O(k)  (for the answer array; excludes input)
        int n = arr.size();
        vector<int> ans(k); // pre-sized array to fill with k closest elements

        // --------------------------------------------------------
        // EDGE CASE 1: x is smaller than every element in arr.
        // The k closest elements are trivially just the first k
        // elements (they're all bigger than x, but nothing is closer).
        // --------------------------------------------------------
        if (x < arr[0]) {
            for (int i = 0; i < k; i++) {
                ans[i] = arr[i];
            }
            return ans;
        }

        // --------------------------------------------------------
        // EDGE CASE 2: x is larger than every element in arr.
        // The k closest elements are the LAST k elements. We fill
        // ans backward (from the end of arr) using two pointers i, j.
        // --------------------------------------------------------
        if (x > arr[n - 1]) {
            int i = n - 1;
            int j = k - 1;
            while (j >= 0) {
                ans[j] = arr[i];
                j--;
                i--;
            }
            return ans;
        }

        // --------------------------------------------------------
        // MAIN CASE: x lies within the array's range.
        // STEP 1: Binary search to find x itself, OR find the
        // "insertion point" boundaries around where x would sit.
        // --------------------------------------------------------
        int low = 0;
        int high = n - 1;
        bool flag = false; // true if x is exactly present in arr
        int t = 0;          // index into ans[] as we fill it
        int mid = -1;

        while (low <= high) {
            mid = low + (high - low) / 2;
            if (arr[mid] == x) {
                flag = true;      // x found directly
                ans[t] = arr[mid]; // x itself is obviously closest (distance 0)
                t++;
                break;
            } else if (arr[mid] > x) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        // --------------------------------------------------------
        // STEP 2: Set up lb (left boundary) and ub (right boundary)
        // — these are the two "tug of war" pointers that will
        // expand outward from wherever x would sit.
        // --------------------------------------------------------
        // If x was NOT found, the binary search loop naturally ends
        // with high = largest index where arr[high] < x, and
        // low = smallest index where arr[low] > x. These ARE the
        // correct starting boundaries already — no adjustment needed.
        int lb = high; // lower bound (candidate on the left)
        int ub = low;  // upper bound (candidate on the right)

        // If x WAS found at mid, we've already consumed mid into ans,
        // so the next candidates to compare are mid-1 and mid+1.
        if (flag == true) {
            lb = mid - 1;
            ub = mid + 1;
        }

        // --------------------------------------------------------
        // STEP 3: The "tug of war" expansion.
        // At each step, compare the distance from x to arr[lb] vs
        // arr[ub]. Pick whichever is closer (ties go to the smaller
        // value, i.e., the LEFT side, per problem's tie-breaking rule).
        // --------------------------------------------------------
        while (t < k && lb >= 0 && ub <= n - 1) {
            int d1 = abs(x - arr[lb]);
            int d2 = abs(x - arr[ub]);
            if (d1 <= d2) {
                // Left candidate is closer (or tied) --> pick it.
                // Tie-breaking rule (d1 <= d2, not d1 < d2) ensures
                // smaller values are preferred on equal distance.
                ans[t] = arr[lb];
                lb--; // move left boundary further left
            } else {
                // Right candidate is strictly closer --> pick it.
                ans[t] = arr[ub];
                ub++; // move right boundary further right
            }
            t++; // one element added to ans, regardless of which side won
        }

        // --------------------------------------------------------
        // STEP 4: Cleanup — if we ran out of room on the LEFT side
        // (lb < 0) before filling k elements, all remaining picks
        // MUST come from the right side.
        // --------------------------------------------------------
        if (lb < 0) {
            while (t < k) {
                ans[t] = arr[ub];
                ub++;
                t++;
            }
        }

        // --------------------------------------------------------
        // STEP 5: Cleanup — if we ran out of room on the RIGHT side
        // (ub > n-1) before filling k elements, all remaining picks
        // MUST come from the left side.
        // --------------------------------------------------------
        if (ub > n - 1) {
            while (t < k) {
                ans[t] = arr[lb];
                lb--;
                t++;
            }
        }

        // The k elements were picked in "closest-first" order, not
        // sorted order, so we sort before returning as required.
        sort(ans.begin(), ans.end()); // WORST CASE = O(k log k)
        return ans;
    }
};

// ============================================================
// SUMMARY BLOCK FOR REVISION (read this first when revisiting)
// ============================================================
//
// PLAIN ENGLISH DEFINITION:
// Given a sorted array, find the k values closest to x. Ties in
// distance go to the smaller value. Return the result sorted.
//
// THE ANALOGY (for permanent memory):
// x is a person standing at a spot in a sorted line. Binary search
// gets you to roughly where x would stand. Then you look one step
// left and one step right — whoever is closer to x gets picked
// first, like a tug of war where the closer side always wins the
// next pick. Keep doing this until you've picked k people.
//
// THE CORE TRICK (three-part structure):
//   1. Handle the two trivial edge cases first: x below the whole
//      array, or x above the whole array — the answer is just the
//      first k or last k elements, no searching needed.
//   2. Binary search for x (or its would-be position) to anchor
//      your two pointers (lb, ub) at the right starting spot.
//   3. Expand lb and ub outward, always picking whichever side is
//      closer to x, until you've collected k elements.
//
// STEP-BY-STEP MENTAL CHECKLIST:
//   1. If x < arr[0]  --> return first k elements.
//   2. If x > arr[n-1] --> return last k elements.
//   3. Binary search for x:
//        - If found, ans[0] = x, lb = mid-1, ub = mid+1.
//        - If not found, lb = high, ub = low (natural boundaries
//          from the failed binary search).
//   4. While t < k and both lb, ub are in bounds:
//        - Compare abs(x-arr[lb]) vs abs(x-arr[ub]).
//        - Pick the closer one (ties favor lb, the smaller value).
//   5. If lb ran out first, fill remaining slots from ub onward.
//   6. If ub ran out first, fill remaining slots from lb backward.
//   7. Sort the k picked elements before returning.
//
// COMPLEXITY:
//   Time  -> O(log n + k log k): O(log n) to anchor via binary
//            search, O(k) to expand the two pointers, and O(k log k)
//            to sort the final small answer array.
//   Space -> O(k): only the answer array (excluding input storage).
//
// COMMON MISTAKES TO AVOID:
//   1. Using "d1 < d2" instead of "d1 <= d2" in the tie-breaking
//      comparison. The problem requires ties to favor the SMALLER
//      value, and since lb is always the left/smaller candidate,
//      "<=" correctly gives it priority on a tie.
//   2. Forgetting the two boundary cleanup loops (when lb < 0 or
//      ub > n-1). Without them, if the anchor point is near either
//      edge of the array, you'd run out of one side and fail to
//      fill all k slots.
//   3. Not realizing the failed-binary-search case already gives
//      you correct lb/ub boundaries for free (lb = high, ub = low).
//      Some implementations redundantly re-derive these with extra
//      logic when the loop's natural exit state already has them.
//
// TRIGGER WORDS TO RECOGNIZE THIS PATTERN INSTANTLY:
//   "k closest elements", "k nearest values in a sorted array",
//   "closest to x with tie-breaking" --> think binary search to
//   anchor position, then two-pointer expansion outward.
//
// WHERE THIS SHOWS UP IN INTERVIEWS:
//   Common at Amazon, Bloomberg, and Google — often as a follow-up
//   to basic binary search once interviewers see you're comfortable
//   with the core pattern. Related problems:
//   - LeetCode 35: Search Insert Position (the "anchor" sub-step alone)
//   - LeetCode 34: Find First and Last Position of Element in Sorted Array
// ============================================================