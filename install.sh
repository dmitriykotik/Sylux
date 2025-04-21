#!/bin/bash

cat <<'EOF'
   _____       _              _  __                    _  
  / ____|     | |            | |/ /                   | | 
 | (___  _   _| |_   ___  __ | ' / ___ _ __ _ __   ___| | 
  \___ \| | | | | | | \ \/ / |  < / _ \ '__| '_ \ / _ \ | 
  ____) | |_| | | |_| |>  <  | . \  __/ |  | | | |  __/ | 
 |_____/ \__, |_|\__,_/_/\_\ |_|\_\___|_|  |_| |_|\___|_| 
          __/ |                                           
         |___/                                            
EOF

echo "Installing .NET Runtime 9.0..."
sudo wget https://dot.net/v1/dotnet-install.sh -O dotnet-install.sh
sudo bash dotnet-install.sh --channel 9.0
rm dotnet-install.sh
echo "Installing Make for Sylux..."
sudo wget https://github.com/dmitriykotik/Sylux-Maker/releases/download/v0.1.1.41/Make
sudo chmod +x ./Make
echo "Downloading additional packages..."
./Make install_i686
echo "Installation is complete! Read the documentation before use: https://github.com/dmitriykotik/Sylux"