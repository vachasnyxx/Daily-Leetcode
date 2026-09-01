// class Solution {
// public:
//     int findwinnerIdx(int n, int k) {
//         if (n == 1) {
//             return 0;
//         }

//         int idx = findwinnerIdx(n - 1, k);
//         idx = (idx + k) % n;
//         return idx;
//     }
//     int findTheWinner(int n, int k) {
//         int result_idx = findwinnerIdx(n, k);

//         return result_idx + 1;
//     }
// };



// ============================================================
// LeetCode 1823 - Find the Winner of the Circular Game
// Pattern: JOSEPHUS PROBLEM (recursive elimination in a circle)
// ============================================================

class Solution {
public:

    // --------------------------------------------------------
    // findwinnerIdx(n, k)
    // Returns the 0-INDEXED position of the winner, assuming
    // people are numbered 0, 1, 2, ..., n-1 standing in a circle.
    //
    // WHY 0-indexed? Because modulo arithmetic (%) is clean and
    // "wraps around" naturally only when positions start at 0.
    // If we used 1-indexing, every mod operation would need an
    // extra +1/-1 correction. So we solve in 0-indexed world,
    // then convert to 1-indexed only at the very end.
    // --------------------------------------------------------
    int findwinnerIdx(int n, int k) {

        // ---------------- BASE CASE ----------------
        // If there's only 1 person left in the circle,
        // that person IS the winner, standing at position 0
        // (since with n=1, the only valid index is 0).
        if (n == 1) {
            return 0;
        }

        // ---------------- RECURSIVE LEAP OF FAITH ----------------
        // "Trust the recursion": assume findwinnerIdx(n-1, k)
        // ALREADY correctly tells us the winner's position when
        // there were only (n-1) people in the circle.
        //
        // The key trick of Josephus Problem: think BACKWARDS.
        // Instead of simulating n people and removing one by one
        // (which is the natural but harder way to think forward),
        // we imagine we already know the answer for a SMALLER
        // circle of (n-1) people, and figure out how adding the
        // n-th person shifts that answer.
        int idx = findwinnerIdx(n - 1, k);

        // ---------------- THE SHIFT FORMULA ----------------
        // Here's the intuition:
        // Suppose with (n-1) people, the winner was found at
        // position `idx` (0-indexed, relative to a circle of n-1).
        //
        // Now imagine we ADD the n-th person into the circle,
        // BEFORE the elimination even starts, and then perform
        // the very first elimination step (counting k people and
        // removing the k-th one, 0-indexed position (k-1)%n).
        //
        // After that first removal, the circle that remains is
        // EXACTLY the same relative circle of (n-1) people from
        // before -- just rotated/shifted by k positions because
        // counting restarted after the person at index (k-1)%n
        // was eliminated.
        //
        // So: new_position_in_n_circle = (old_position_in_(n-1)_circle + k) % n
        //
        // This is why we do: idx = (idx + k) % n
        // We're "unwinding" the recursion: converting the known
        // winner position in a SMALLER circle into the correct
        // winner position in the CURRENT (one person bigger) circle.
        idx = (idx + k) % n;

        // Return this corrected position -- it becomes the `idx`
        // that the CALLER (findwinnerIdx for n+1) will use next.
        return idx;
    }

    // --------------------------------------------------------
    // findTheWinner(n, k)
    // The actual LeetCode-required function. LeetCode wants a
    // 1-INDEXED answer (person numbered 1 to n), but our helper
    // works in 0-indexed space for clean math. So we just add 1
    // at the very end to convert back.
    // --------------------------------------------------------
    int findTheWinner(int n, int k) {
        int result_idx = findwinnerIdx(n, k);   // 0-indexed winner position
        return result_idx + 1;                   // convert to 1-indexed answer
    }
};

/*
============================================================
REVISION SUMMARY (read this when you forget everything else)
============================================================

WHAT IS THIS PROBLEM?
n people stand in a circle, numbered 1 to n. Starting from
person 1, you count k people (wrapping around the circle) and
eliminate the k-th person. You keep repeating this, always
continuing the count from the next person, until only ONE
person remains. That person is the winner. Find their number.

ANALOGY - "Duck Duck Goose, but brutal":
Imagine kids sitting in a circle playing duck-duck-goose, but
every time you say "GOOSE" on the k-th kid, that kid is OUT and
leaves the circle immediately (chair and all). The circle gets
smaller and smaller, and you just keep counting from where you
left off. Eventually one kid is left sitting alone -- that's
your answer.

THE CORE INTUITION - "Building the circle backwards, like nesting dolls":
Simulating this FORWARD (n people, remove one by one, shrink
circle) is what most people try first -- and it works with a
list/queue, but it's harder to reason about mathematically and
can be less efficient to prove correct.

The elegant trick: think RECURSIVELY and BACKWARDS.
- Solve the tiny version first: "If there was only 1 person,
  they trivially win at position 0."
- Then ask: "If I already know the winning position for a
  circle of (n-1) people, can I DERIVE the winning position for
  a circle of n people, without resimulating everything?"
- Answer: YES. Adding the n-th person and doing ONE elimination
  round just ROTATES the previously-known answer by k positions
  (mod n, to wrap around the bigger circle).
- This is like Russian nesting dolls: solve the innermost doll
  (n=1) first, then each outer doll "wraps" the inner answer
  using the formula (idx + k) % n.

DRY RUN EXAMPLE (n=5, k=2):
- n=1: idx = 0                              (trivial winner)
- n=2: idx = (0 + 2) % 2 = 0
- n=3: idx = (0 + 2) % 3 = 2
- n=4: idx = (2 + 2) % 4 = 0
- n=5: idx = (0 + 2) % 5 = 2
- Final answer (1-indexed) = 2 + 1 = 3
  (LeetCode's own example for n=5, k=2 gives winner = 3. Matches!)

TIME COMPLEXITY: O(n)
  We make exactly one recursive call per value from n down to 1,
  and each call does O(1) work (just one addition and one mod).
  So total work = O(n).

SPACE COMPLEXITY: O(n)
  This is NOT O(1) even though we don't use extra data
  structures explicitly! Why? Because RECURSION uses the CALL
  STACK. Each recursive call to findwinnerIdx(n-1, k) sits on
  the stack waiting for its answer, so at the deepest point we
  have n stack frames alive at once. That's O(n) space.
  (You CAN convert this to an O(1)-space iterative version using
  a simple for-loop that builds idx from n=1 up to n=n. Good
  follow-up to try yourself!)

COMMON MISTAKES WITH THIS PATTERN:
1. Forgetting to convert between 0-indexed math and 1-indexed
   output. The recursion is cleanest in 0-indexed space; only
   the FINAL return needs +1.
2. Trying to trace the recursion FORWARD (n=1 to n=5) in your
   head as "removing people," when really the recursion builds
   UP from the base case -- the "removal" intuition applies to
   how the formula was DERIVED, not how you should trace the
   code execution.
3. Confusing this with a simple queue/simulation approach and
   assuming it must always be simulated with a data structure --
   the recursive formula is more elegant and interview-impressive
   once you understand why the rotation works.

TRIGGER WORDS TO SPOT THIS PATTERN:
"people in a circle," "eliminate every k-th," "last person
remaining," "circular elimination," "safe position" -- these
scream "Josephus Problem." Whenever you see repeated elimination
in a circular structure with a fixed counting step, think of
this recursive rotation trick.

WHERE THIS PATTERN SHOWS UP:
Josephus Problem is a favorite in academic DSA courses and
occasionally shows up in interview rounds testing recursion and
mathematical pattern-recognition (seen referenced in interview
prep sets for companies like Amazon and in various product-based
company OA rounds, often as a "circular counting" variant).
============================================================
*/






















// using queue
// class Solution {
// public:
//     int findTheWinner(int n, int k) {
//         queue<int> que;

//         for(int i = 1; i<= n; i++){
//             que.push(i);
//         }

//         while(que.size() > 1){
//             for(int count = 1; count <= k -1; count++){
//                 que.push(que.front());
//                 que.pop();
//             }

//             que.pop();
//         }

//         return que.front();
//     }
// };












// approach of simulation and using array
// class Solution {
// public:
//     int findTheWinner(int n, int k) {
//         vector<int> arr;

//         for(int i = 1; i<= n; i++){
//             arr.push_back(i);
//         }

//         int i = 0;// game starts from 1st player which is sitting at index 0

//         while(arr.size() > 1){
//             int idx = (i + k - 1) % arr.size();

//             arr.erase(arr.begin() + idx);

//             i = idx;
//         }

//         return arr[0];
//     }
// };