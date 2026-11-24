# PowerShell commands — Smart Forest Monitoring

PC path: `..:\....\....\.....`

## 1. Initial installation (one time)

**Check existing tools:**

```powershell
python --version
git --version
cmake --version
ninja --version
```

**Install missing tools:**

```powershell
winget install --id Kitware.CMake -e
winget install --id Ninja-build.Ninja -e
winget install --id 7zip.7zip -e
```

**Create Zephyr workspace:**

```powershell
cd `..:\....\....\.....` (local project path)
mkdir zephyrproject
cd zephyrproject
python -m venv .venv
.\.venv\Scripts\python.exe -m pip install west
.\.venv\Scripts\west.exe init -m https://github.com/zephyrproject-rtos/zephyr
.\.venv\Scripts\west.exe update
.\.venv\Scripts\python.exe -m pip install -r .\zephyr\scripts\requirements.txt
.\.venv\Scripts\west.exe zephyr-export
```

**Install ARM SDK:**

```powershell
$env:Path = "C:\Program Files\7-Zip;$env:Path"
.\.venv\Scripts\west.exe sdk install --gnu-toolchains arm-zephyr-eabi
```

## 2. New PowerShell window

```powershell
cd `..:\....\....\.....` (local project path)
```

No need to reinstall tools or activate `.venv` when using its `west.exe` directly.

## 3. Build firmware

**After editing `main.c`:**

```powershell
.\.venv\Scripts\west.exe build -d build-sensor
```

**Clean build (e.g., Devicetree/configuration changes):**

```powershell
.\.venv\Scripts\west.exe build -b xiao_ble/nrf52840 ..\firmware\sensor_node -d build-sensor --pristine
```

**Initial `hello_world` test:**

```powershell
.\.venv\Scripts\west.exe build -b xiao_ble/nrf52840 zephyr/samples/hello_world -d build-hello
```

## 4. Flash to XIAO nRF52840

- Stop Serial Monitor.
- Double-press RESET → UF2 drive `XIAO-SENSE` appears.
- Check drive letter (initially `E:`).

```powershell
Copy-Item .\build-sensor\zephyr\zephyr.uf2 'E:\'
```

- The drive disappears after reboot.
- VS Code Serial Monitor: **COM port** (initially COM9), **115200 baud**.
- Single RESET = restart firmware; double RESET = bootloader.

## 5. Git / GitHub

**Initial setup:**

```powershell
cd `..:\....\....\.....`(local project path)
git init -b main
git remote add origin https://github.com/....../......git (link git repository)
```

**Everyday changes:**

```powershell
cd `..:\....\....\.....`(local project path)
git status
git add ....
git commit -m "message"
git push origin main
```

Keep `zephyrproject/` in `.gitignore`; do **not** upload Zephyr sources or `.venv`.
