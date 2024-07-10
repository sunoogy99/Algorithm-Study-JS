const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let count = 0;
let home = [];

class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

class Queue {
    constructor() {
        this.front = null;
        this.rear = null;
    }

    isEmpty() {
        return this.front === null && this.rear === null;
    }

    enqueue(item) {
        const newNode = new Node(item);
        if (this.isEmpty()) this.front = newNode;
        else this.rear.next = newNode;
        this.rear = newNode;
    }

    dequeue() {
        if (this.isEmpty()) return;
        const peekNode = this.front.data;
        this.front = this.front.next;
        if (!this.front) this.rear = null;
        return peekNode;
    }

    peek() {
        if (this.isEmpty()) return -1;
        return this.front.data;
    }
}

const solution = (N, home) => {
    // N 범위 : 3 ~ 16 => 완전 탐색 가능
    // BFS 방식으로 풀 거임. Queue에 넣는 데이터는 [start1, end1, start2, end2] 지점

    // 예외 처리 - 마지막에 벽이 있는 경우, 파이프를 넣을 수 없음
    // 완전 탐색 시, 벽이 있는 경우에 대해 시간 초과 걸려서 예외 처리함
    if (home[N - 1][N - 1] === 1) return 0;

    let visitCount = Array.from(Array(N), () => Array(N).fill(0));

    const inRange = (x1, y1, x2, y2) => x1 >= 0 && x1 < N && y1 >= 0 && y1 < N && x2 >= 0 && x2 < N && y2 >= 0 && y2 < N;
    const canGo = (x1, y1, x2, y2) => {
        // 가로, 세로 이동의 경우
        if (x1 === x2 || y1 === y2) {
            if (!inRange(x1, y1, x2, y2)) return false;
            else if (home[x1][y1] || home[x2][y2]) return false;
            else return true;
        }
        // 대각선 이동의 경우, (x2 - 1, y2)와 (x2, y2 - 1)은 (x2, y2)가 범위 안에 있다면 자동적으로 범위 이내에 있음
        else {
            if (!inRange(x1, y1, x2, y2)) return false;
            else if (home[x1][y1] || home[x2][y2] || home[x2 - 1][y2] || home[x2][y2 - 1]) return false;
            else return true;
        }
    }


    // 0-based index로 설정함
    const queue = new Queue();
    // x1 y1 x2 y2 순서
    queue.enqueue([0, 0, 0, 1]);

    while (!queue.isEmpty()) {
        const [sx, sy, ex, ey] = queue.dequeue();

        // 가로로 놓인 경우
        if (sx === ex) {
            // 우로 이동
            if (canGo(sx, sy + 1, ex, ey + 1)) {
                queue.enqueue([sx, sy + 1, ex, ey + 1]);
                visitCount[ex][ey + 1] += 1;
            }
            
            // 대각선 이동
            if (canGo(sx, sy + 1, ex + 1, ey + 1)) {
                queue.enqueue([sx, sy + 1, ex + 1, ey + 1]);
                visitCount[ex + 1][ey + 1] += 1;
            }
        }
        // 세로로 놓인 경우
        else if (sy === ey) {
            // 아래로 이동
            if (canGo(sx + 1, sy, ex + 1, ey)) {
                queue.enqueue([sx + 1, sy, ex + 1, ey]);
                visitCount[ex + 1][ey] += 1;
            }
            // 대각선 이동
            if (canGo(sx + 1, sy, ex + 1, ey + 1)) {
                queue.enqueue([sx + 1, sy, ex + 1, ey + 1]);
                visitCount[ex + 1][ey + 1] += 1;
            }
        }
        // 대각선으로 놓인 경우
        else {
            // 가로 방향 이동
            if (canGo(sx + 1, sy + 1, ex, ey + 1)) {
                queue.enqueue([sx + 1, sy + 1, ex, ey + 1]);
                visitCount[ex][ey + 1] += 1;
            }
            // 세로 방향 이동
            if (canGo(sx + 1, sy + 1, ex + 1, ey)) {
                queue.enqueue([sx + 1, sy + 1, ex + 1, ey]);
                visitCount[ex + 1][ey] += 1;
            }
            // 대각선 방향 이동
            if (canGo(sx + 1, sy + 1, ex + 1, ey + 1)) {
                queue.enqueue([sx + 1, sy + 1, ex + 1, ey + 1]);
                visitCount[ex + 1][ey + 1] += 1;
            }
        }
    }

    return visitCount[N - 1][N - 1];
}

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    } else {
        home.push(line.split(' ').map(e => +e));
        count++;
    }

    if (count === N) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(N, home);
    console.log(res);
    process.exit();
});