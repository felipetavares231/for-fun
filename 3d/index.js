const ctx = game.getContext("2d");

// ---------- Math / Engine ----------

function getCanvasPoint(x, y) {
    return {
        x: game.width / 2 + x,
        y: game.height / 2 - y
    };
}

function project(x, y, z) {
    const f = 600;
    return {
        x: (x * f) / z,
        y: (y * f) / z
    };
}

function rotateY(x, y, z, angle) {
    return {
        x: x * Math.cos(angle) - z * Math.sin(angle),
        y: y,
        z: x * Math.sin(angle) + z * Math.cos(angle)
    };
}

function rotateX(x, y, z, angle) {
    return {
        x: x,
        y: y * Math.cos(angle) - z * Math.sin(angle),
        z: y * Math.sin(angle) + z * Math.cos(angle)
    };
}

function drawLine(p1, p2) {
    ctx.beginPath();
    ctx.moveTo(p1.x, p1.y);
    ctx.lineTo(p2.x, p2.y);
    ctx.stroke();
}

function createBox(cx, cy, cz, w, h, d) {
    w/=2; h/=2; d/=2;

    const v = [
        {x:cx-w,y:cy-h,z:cz-d},
        {x:cx+w,y:cy-h,z:cz-d},
        {x:cx+w,y:cy+h,z:cz-d},
        {x:cx-w,y:cy+h,z:cz-d},
        {x:cx-w,y:cy-h,z:cz+d},
        {x:cx+w,y:cy-h,z:cz+d},
        {x:cx+w,y:cy+h,z:cz+d},
        {x:cx-w,y:cy+h,z:cz+d},
    ];

    const e = [
        [0,1],[1,2],[2,3],[3,0],
        [4,5],[5,6],[6,7],[7,4],
        [0,4],[1,5],[2,6],[3,7]
    ];

    return { vertices:v, edges:e };
}

// ---------- Car Model ----------

// main body
const chassis = createBox(0, 0, 0, 420, 80, 160);

// hood
const hood = createBox(180, 20, 0, 160, 60, 150);

// rear trunk
const trunk = createBox(-190, 20, 0, 120, 60, 150);

// cabin base
const cabinBase = createBox(-20, 80, 0, 220, 70, 150);

// roof
const roof = createBox(-40, 140, 0, 160, 40, 140);

// front bumper
const bumper = createBox(260, -10, 0, 40, 40, 140);

// wheels (thinner depth)
const wheelFL = createBox(130, -70, 90, 90, 90, 40);
const wheelFR = createBox(130, -70, -90, 90, 90, 40);
const wheelBL = createBox(-130, -70, 90, 90, 90, 40);
const wheelBR = createBox(-130, -70, -90, 90, 90, 40);

const carParts = [
    chassis,
    hood,
    trunk,
    cabinBase,
    roof,
    bumper,
    wheelFL, wheelFR,
    wheelBL, wheelBR
];

// ---------- Animation ----------

let angleY = 0;
let angleX = -0.2;

function frame() {
    ctx.fillStyle = "black";
    ctx.fillRect(0,0,game.width,game.height);

    ctx.strokeStyle = "#00FFAA";

    for (let part of carParts) {

        const transformed = [];

        for (let v of part.vertices) {

            let r = rotateX(v.x, v.y, v.z, angleY);
            r = rotateY(r.x, r.y, r.z, angleX);

            r.z += 1000;

            let p = project(r.x, r.y, r.z);
            transformed.push(getCanvasPoint(p.x, p.y));
        }

        for (let e of part.edges) {
            drawLine(transformed[e[0]], transformed[e[1]]);
        }
    }

    angleY += 0.01;

    requestAnimationFrame(frame);
}

frame();
