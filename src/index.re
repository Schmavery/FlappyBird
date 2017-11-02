open Reprocessing;

let g = 25.;

let hSpeed = 4.;

let birdRad = 15.;

let scrollRate = 100.;

let jumpSpeed = (-12.);

let pipeColor = Utils.color r::80 g::185 b::0 a::255;

type pipeT = (float, float);

type stateT = {
  pos: (float, float),
  vy: float,
  running: bool,
  pipes: list pipeT,
  score: int,
  angle: float,
  font: Reprocessing.fontT,
  img: Reprocessing.imageT
};


let gapRadius = 60.;

let pipeWidth = 75.;

let birdX = 150.;

let minInterPipeGap = 120. +. pipeWidth;

let intersectPipe birdPos (centerX, gapCenterY) env :bool => {
  let pipeRad = pipeWidth /. 2.;
  let height = float_of_int (Env.height env);
  let tophit =
    Utils.intersectRectCircle
      rectPos::(centerX -. pipeRad, 0.)
      rectW::pipeWidth
      rectH::(gapCenterY -. gapRadius)
      circlePos::birdPos
      circleRad::birdRad;
  let bottomhit =
    Utils.intersectRectCircle
      rectPos::(centerX -. pipeRad, gapCenterY +. gapRadius)
      rectW::pipeWidth
      rectH::(height -. gapCenterY -. gapRadius)
      circlePos::birdPos
      circleRad::birdRad;
  tophit || bottomhit
};

let drawPipe (centerX, gapCenterY) env => {
  let pipeRad = pipeWidth /. 2.;
  let height = float_of_int (Env.height env);
  Draw.fill pipeColor env;
  Draw.rectf
    pos::(centerX -. pipeRad, 0.)
    width::pipeWidth
    height::(gapCenterY -. gapRadius)
    env;
  Draw.rectf
    pos::(centerX -. pipeRad, gapCenterY +. gapRadius)
    width::pipeWidth
    height::(height -. gapCenterY -. gapRadius)
    env
};

let setup env :stateT=> {
  Env.size width::400 height::640 env;
  Draw.noStroke env;
  {
    pos: (birdX, 40.),
    vy: 0.,
    running: true,
    pipes: [(300., 100.), (500., 100.), (700., 150.), (900., 230.)],
    score: 0,
    angle: 0.,
    font: Draw.loadFont filename::"./assets/flappy.fnt" isPixel::true env,
    img: Draw.loadImage filename::"./assets/flappy.png" isPixel::true env
  }
};

let show_state ({pos: (x, y)}: stateT) :string =>
  Printf.sprintf "{x: %f, y: %f}" x y;

let crashed {running, pos: (_, y)} env =>
  not running && float_of_int (Env.height env) -. birdRad -. y < 1.;

let draw ({pos: (x, y) as pos, vy, running, pipes, font, img} as state) env => {
  let timeStep = Env.deltaTime env;
  Draw.background (Utils.color r::230 g::230 b::250 a::255) env;
  List.iter (fun (pipe: pipeT) => drawPipe pipe env) pipes;
  Draw.fill Constants.red env;
  /* Draw.ellipsef center::state.pos radx::birdRad rady::birdRad env; */
  Draw.pushMatrix env;
  let drawBirdRad = birdRad +. 5.;
  Draw.translate ::x ::y env;
  Draw.rotate state.angle env;
  Draw.translate x::(-. drawBirdRad) y::(-. drawBirdRad) env;
  Draw.subImage
    img
    pos::(0, 0)
    width::(int_of_float drawBirdRad * 2)
    height::(int_of_float drawBirdRad * 2)
    texPos::(3, 488)
    texWidth::17
    texHeight::17
    env;
  Draw.popMatrix env;
  let halfPipeWidth = pipeWidth /. 2.;
  let screenHeight = float_of_int (Env.height env);
  Draw.pushMatrix env;
  Draw.translate x::(float_of_int (Env.width env / 2 - 20)) y::50. env;
  Draw.scale x::3. y::3. env;
  Draw.text ::font body::(string_of_int state.score) pos::(0, 0) env;
  Draw.popMatrix env;
  if (not running) {
    Draw.subImage
      img
      pos::((Env.width env - 98 * 3) / 2, Env.height env / 2 - 20)
      width::(98 * 3)
      height::(23 * 3)
      texPos::(393, 59)
      texWidth::98
      texHeight::23
      env
  };
  let hit = List.exists (fun pipe => intersectPipe pos pipe env) pipes;
  let maxPipeX = List.fold_left (fun acc (x, _y) => max acc x) 0. pipes;
  let (newPipes, newScore) =
    crashed state env ?
      (pipes, state.score) :
      List.fold_left
        (
          fun (pipes, score) (x, y) => {
            let (newX, _) as newPos =
              if (x < -. halfPipeWidth) {
                (
                  maxPipeX +.
                  Utils.randomf
                    min::minInterPipeGap max::(2. *. minInterPipeGap),
                  Utils.randomf min::gapRadius max::(screenHeight -. gapRadius)
                )
              } else {
                (x -. scrollRate *. timeStep, y)
              };
            (
              [newPos, ...pipes],
              score + (running && newX < birdX && x >= birdX ? 1 : 0)
            )
          }
        )
        ([], state.score)
        pipes;
  {
    ...state,
    pos: (
      x,
      Utils.constrain
        amt::(y +. vy *. g *. timeStep)
        low::birdRad
        high::(screenHeight -. birdRad)
    ),
    vy: vy +. g *. timeStep,
    running: state.running && not hit,
    angle: {
      let highAngle = (-1.2);
      let targetAngle =
        Utils.remapf
          value::vy low1::jumpSpeed high1::10. low2::highAngle high2::0.7;
      let newVal =
        Utils.lerpf
          value::(vy > 0. ? 0.1 : 0.7) low::state.angle high::targetAngle;
      Utils.constrain amt::newVal low::highAngle high::0.7
    },
    pipes: newPipes,
    score: newScore
  }
};

let keyPressed state env =>
  Events.(
    switch (state.running, crashed state env, Env.keyCode env) {
    | (true, false, Space) => {...state, vy: jumpSpeed}
    | (false, true, Space) => setup env
    | _ => state
    }
  );


run ::setup ::draw ::keyPressed ();
