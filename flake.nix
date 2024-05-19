{
    description = "an opengl project";
    inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    outputs = { self, nixpkgs, ... } :
    let
        system = "x86_64-linux";
        pkgs = import nixpkgs { inherit system; };

        run = pkgs.writeShellScriptBin "run" ''
            make clean && make && make run
        '';
    in{
        devShells."${system}".default = pkgs.mkShell {
            packages = with pkgs; [
                glfw
                glew
            ];

            buildInputs = [ 
                run 
            ];

            shellHook = ''
                exec zsh
            '';
        };
    };
}
