import subprocess

def run_tests(file_path):
    with open(file_path) as f:
        lines = f.readlines()

    total = len(lines)
    passed = 0

    for line in lines:
        line = line.strip()
        if not line:
            continue
        
        # Divide o comando e a saída esperada
        parts = line.split(',')
        if len(parts) != 2:
            print(f"Formato inválido: {line}")
            continue

        command_str = parts[0]
        expected = parts[1]
        args = command_str.split()  # divide python dna.py databases/... sequences/...
        
        # Executa o comando
        try:
            result = subprocess.run(args, capture_output=True, text=True)
            output = result.stdout.strip()

            if output == expected:
                print(f"[✔] {command_str} => {output}")
                passed += 1
            else:
                print(f"[✘] {command_str} => {output} (esperado: {expected})")
        except Exception as e:
            print(f"[⚠] Erro ao rodar: {command_str}\n{e}")

    print(f"\n{passed}/{total} testes passaram.")


# Substitua pelo nome do seu arquivo de comandos
run_tests("tests.txt")
