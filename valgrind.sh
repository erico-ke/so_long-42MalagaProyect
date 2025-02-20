mkdir -p leaks # Crea la carpeta 'leaks' si no existe

for file in maps/*; do
    # Obtén el nombre base del archivo sin la extensión
    log_file="leaks/$(basename "$file" .ber).txt"

    echo "Ejecutando Valgrind para $file y guardando en $log_file"
    valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp --log-file="$log_file" ./so_long "$file"
done

# Comando general sin supress
# valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp --log-file=log_leaks -s ./So_Long maps/
