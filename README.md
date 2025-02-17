# AI-Project-1

Installing webassembly <br /> 
&ensp; Mac: <br />
  &ensp;  &ensp; Install homebrew: <br /> 
      &emsp; &emsp; /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)" <br /> 
  &ensp;  &ensp; Install emscripten: <br /> 
      &emsp; &emsp; brew install emscripten <br /> <br /> 
&ensp; Windows: <br />
   &ensp;  &ensp; Install git for windows: <br /> 
         &emsp; &emsp; https://git-scm.com/downloads/win <br />
   &ensp;  &ensp; Install python 3: <br /> 
         &emsp; &emsp; https://www.python.org/downloads/ <br />
   &ensp;  &ensp; Install Visual Studio Build Tools: <br />
          &emsp; &emsp; https://visualstudio.microsoft.com/visual-cpp-build-tools/ <br />
   &ensp;  &ensp; Install Emscripten SDK <br />
          &ensp;  &ensp; Clone the Emscripten SDK Repository: <br />
            &emsp; &emsp;git clone https://github.com/emscripten-core/emsdk.git <br />
          &ensp;  &ensp; Change to the emsdk directory: <br />
                &emsp; &emsp; cd emsdk <br />
          &ensp;  &ensp; Install the Latest Version of Emscripten: <br />
                 &emsp; &emsp; emsdk install latest <br />
          &ensp;  &ensp; Activate the Latest Version: <br />
              &emsp; &emsp; emsdk activate latest <br />
          &ensp;  &ensp; Set Up Environment Variables: <br />
                 &emsp; &emsp; emsdk_env.bat <br />
                  
         

Compiling the code: <br /> 
&ensp; Mac: <br />
     &ensp;  Compile C++ Code into WebAssembly: <br /> 
      &emsp; &emsp; emcc diagnosis.cpp -o diagnosis.js -s WASM=1 -s EXPORTED_FUNCTIONS='["_diagnoseCancer", "_initialize"]' -s EXPORTED_RUNTIME_METHODS='["cwrap"]' <br /> 
   &ensp; Run WebAssembly in the Browser <br />
      &emsp; &emsp; python3 -m http.server 8000 (edit 8000 to whatever port you'll be using) <br /> 
   &ensp; Open: <br /> 
      &emsp; &emsp; http://localhost:8000/index.html (edit 8000 to whatever port you'll be using) <br /> <br /> 
&ensp; Windows: <br />
      &ensp;  Compile C++ Code into WebAssembly: <br /> 
             &emsp; &emsp; emcc example.cpp -o example.html <br />
      &ensp; Run WebAssembly in the Browser <br />
            &emsp; &emsp; python -m http.server 8000 (edit 8000 to whatever port you'll be using) <br />
      &ensp; Open: <br />
            &emsp; &emsp; http://localhost:8000/example.html (edit 8000 to whatever port you'll be using) <br />

