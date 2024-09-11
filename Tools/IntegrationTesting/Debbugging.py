import pytest

def test_spi_init():
    output_file = 'O:\\Jenkins\\workspace\\_SPIH-CI_Brightskies_main\\Tools\\IntegrationTesting\\out.txt'

    # Read the output file
    with open(output_file, 'r') as file:
        output = file.read()

    # Print the output to the console with clear formatting
    print("=== GDB Output ===")
    print(output)
    print("===================")

    # Check if the expected value is present in the output
    expected_value = '$1 = 1'
    assert expected_value in output, f'SPI Enable check failed. Expected value "{expected_value}" not found in GDB output.'

if __name__ == "__main__":
    pytest.main(['-v', '--tb=short'])