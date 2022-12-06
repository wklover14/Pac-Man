Write-Output "Hi Dear player, Nous allons installer PAC-MAN sur votre machine"
gcc --version
if ( $LASTEXITCODE  -eq 0   ) {
     <# On lance l'application  #>
    Get-ChildItem 
    gcc ./Main.c -o Pac-Man
    if ( $LASTEXITCODE  -eq 0  ) {
        <# Action to perform if the condition is true #>
        Write-Output "Compilation ok.."
        Start-Sleep (3)
        Start-Process Pac-Man   
    } else {
        Write-Output "Problemes de compilation !! ci dessous un tuto pour l'installer"
        Write-Output "https://frameboxxindore.com/fr/android/quick-answer-how-do-you-install-gcc-in-windows-10-using-cmd.html"
    }
} else {
    <# On installe gcc  #>
    Write-Output "Veuillez installez GCC sur la machine"
} 
Start-Sleep (5)



