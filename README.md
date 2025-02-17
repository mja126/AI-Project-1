# AI-Project-1

Installing webassembly <br /> 
   &ensp; Install homebrew: <br /> 
      &emsp; &emsp; /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)" <br /> 
   &ensp; Install emscripten: <br /> 
      &emsp; &emsp; brew install emscripten <br /> <br /> 

Compiling the code: <br /> 
   &ensp; Compile: <br /> 
      &emsp; &emsp; emcc diagnosis.cpp -o diagnosis.js -s WASM=1 -s EXPORTED_FUNCTIONS='["_diagnoseCancer", "_initialize"]' -s EXPORTED_RUNTIME_METHODS='["cwrap"]' <br /> 
   &ensp; Run: <br /> 
      &emsp; &emsp; python3 -m http.server 8000 (edit 8000 to whatever port you'll be using) <br /> 
   &ensp; Open: <br /> 
      &emsp; &emsp; http://localhost:8000/index.html (edit 8000 to whatever port you'll be using) <br /> 
