Add-Type -AssemblyName System.Runtime.WindowsRuntime

$connectionProfile = [Windows.Networking.Connectivity.NetworkInformation]::GetInternetConnectionProfile()
$tetheringManager = [Windows.Networking.NetworkOperators.NetworkOperatorTetheringManager]::CreateFromConnectionProfile($connectionProfile)

# Запускаем без ожидания (огня)
$null = $tetheringManager.StartTetheringAsync()

Write-Host "Команда отправлена!" -ForegroundColor Yellow
