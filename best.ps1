# Проверяем, видит ли система хот-спот
try {
    $connectionProfile = [Windows.Networking.Connectivity.NetworkInformation]::GetInternetConnectionProfile()
    Write-Host "Интернет-профиль найден!" -ForegroundColor Green
    
    $tetheringManager = [Windows.Networking.NetworkOperators.NetworkOperatorTetheringManager]::CreateFromConnectionProfile($connectionProfile)
    Write-Host "Менеджер хот-спота создан!" -ForegroundColor Green
    
    $state = $tetheringManager.TetheringOperationalState
    Write-Host "Текущее состояние хот-спота: $state" -ForegroundColor Yellow
    
    if ($state -eq 1) {
        Write-Host "Хот-спот уже включен!" -ForegroundColor Green
    } else {
        Write-Host "Пытаюсь включить..." -ForegroundColor Cyan
        $tetheringManager.EnableTetheringAsync()
        Write-Host "Команда отправлена!" -ForegroundColor Green
    }
} catch {
    Write-Host "ОШИБКА: $_" -ForegroundColor Red
    Write-Host "Тип ошибки: $($_.Exception.GetType().FullName)" -ForegroundColor Red
}

Read-Host "Нажми Enter для выхода"
