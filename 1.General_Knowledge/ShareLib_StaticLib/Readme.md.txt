# README

## Commands

### Make Shared Library
```bash
make shared
```

### Make Static Library
```bash
make static
```

### Run Static Library
```bash
LD_LIBRARY_PATH=./lib/static/ ./bin/use-static-library
```

### Run Shared Library
```bash
LD_LIBRARY_PATH=./lib/shared/ ./bin/use-shared-library
```