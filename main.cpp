#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

class Database{
	public:
		string barcode;

		int tambahDatabase(){
			int count = 0, hargaDatabase;

			while(count == 0){
				string line, isinya;
				vector<string> dataDatabase;
				vector<string>::iterator i;

				fstream doc;
				doc.open("cetak.txt", ios::app);

				fstream Database;
				Database.open("Database.csv", ios::in);


				cout << "\n\nMasukkan Kode Barang: " << endl;
				cin >> barcode;
				fflush(stdin);

				while(getline(Database, line)){

					dataDatabase.clear();

					istringstream s(line);

					while(getline(s, isinya, ',')){
						dataDatabase.push_back(isinya);
					}
					if(dataDatabase[0] == barcode){
						cout << "\nItem: \t\t" << dataDatabase[1] << " "<< endl;
						count = 1;
						doc << "\n" << dataDatabase[1] << "\t\t\tRp." << dataDatabase[2] << endl;
						stringstream ss;
						ss << dataDatabase[2];
						ss >> hargaDatabase;
						cout << "\t\tRp. " << hargaDatabase << endl;
						return hargaDatabase;
					}

				}
				if(count == 0){
					cout << "Barang Tidak Ditemukan" << endl;
				}
				doc.close();
				Database.close();
			}
		}
		int kaliDatabase(){
			int jumlah;
			do{
				fstream doc;
				doc.open("cetak.txt", ios::app);

				cout << "\t\t@";
				cin >> jumlah;

				doc << "\t\t\t\t\t@" << jumlah << endl;

				doc.close();
			}while(jumlah <= 0);

			return jumlah;
		}
		int cekAda(string barcode){
				ifstream dokk("Database.csv");

				string line, bcada;

				while(getline(dokk, line)){
					istringstream s(line);
					getline(s, bcada, ',');
					if(barcode == bcada){
						cout << "\nKode Barang Sudah Ada!\n";
						return 1;
					}
				}

				return 2;
		}
};

class print:public Database{
	public:
		int cetakAwal(){
			int fitur;
				cout << "\n**************************************************************" << endl;
				cout << "**********************CASHIER MEDAN MARKET********************" << endl;
				cout << "**************************************************************\n" << endl;
				cout << "FITUR CASHIER MARKET" << endl;
				cout << "" << endl;
				cout << "1. CEK DATA BARANG" << endl;
				cout << "2. CEK HARGA BARANG" << endl;
				cout << "3. KASIR MEDAN MARKET" << endl;
				cout << "4. TAMBAH BARANG BARU" << endl;
				cout << "" << endl;
				cout << " ---------------------------------------------------------------" << endl;
				cout << "\n**************************************************************" << endl;

				do{
					cout << "CODE : ";
					cin >> fitur;
				}while(fitur > 4 || fitur < 1);

				return fitur;
		}
		void cekDatabase(){
			vector<string> vdata;
			vector<string>::iterator i;

			fstream data;
			data.open("Database.csv", ios::in);

			cout << "\n**************************************************************" << endl;
				cout << "**********************DATA BARANG********************" << endl;
				cout << "**************************************************************\n" << endl;

			cout << "Nomor\tKode Barang \tNama Barang \t\t\tHarga\n" << endl;

			string line, barcode, namaDatabase, harga;

			int j = 1;

			while(getline(data, line)){
				vdata.clear();

				istringstream ss(line);

				cout << j << "\t";
				j++;
				getline(ss, barcode, ',');
				cout << barcode << "\t\t";

				getline(ss, namaDatabase, ',');
				cout << namaDatabase << "\t\t";

				getline(ss, harga, ',');
				cout << harga << "\t";

				cout << "\n";
			}
			cout << "----------------------------------------------\n" << endl;
			data.close();
		}
		void cekHarga(){
			char cl;
			do{
				string barcode, baris, isi;
				int count = 0;

				fstream dataB;
				dataB.open("Database.csv", ios::in);

				vector<string> vekd;
				vector<string>::iterator it;
				cout << "\n\n-------------------------HARGA-------------------------\n" << endl;

				cout << "Isi Kode Barang: " << endl;
				cin >> barcode;

				while(getline(dataB, baris)){
					vekd.clear();

					istringstream ss(baris);

					while(getline(ss, isi, ',')){
						vekd.push_back(isi);
					}
					if(vekd[0] == barcode){
						count = 1;
						cout << "\nItem: " << vekd[1] << "\nHarga: Rp. "<< vekd[2] << "\n" << endl;;
					}
				}
				if(count == 0){
					cout << "Barang Tidak Ditemukan" << endl;
				}
				cout << "Cek lagi? (y/n) " << endl;
				cin >> cl;
			}while(cl == 'y' || cl == 'Y');
		}
		int programKasir(){
			int total = 0, ttemp = 0;
			int a, b;

			vector<string> struk;
			vector<string>::iterator i;
				cout << "\n**************************************************************" << endl;
				cout << "**********************CASHIER MEDAN MARKET********************" << endl;
				cout << "**************************************************************\n" << endl;
			char lagi;

			do{
				fstream doc;
				doc.open("cetak.txt", ios::app);

			    a = tambahDatabase();
				b = kaliDatabase();
				ttemp = a*b;
				doc << "\t\t\t\t\tRp." << ttemp << endl;
				total = total + ttemp;
				cout << "\nHarga:\t\tRp." << ttemp << "\n" << endl;
				cout << "Tambahan Barang Tekan ?" << endl;
				cout << "Bayar Tekan =" << endl;
				cin >> lagi;
				doc.close();
			}while(lagi != '=');

			cout << "\n\nTotal : Rp." << total << endl;
			return total;
		}
		int kembalian(int harganya){
			int uang, kembalian;
			fstream dok;
			dok.open("cetak.txt", ios::app);
			do{

				cout << "Jumlah Dibayar : \nRp.";
				cin >> uang;

				kembalian = uang - harganya;
			}while(kembalian < 0);

			dok << "------------------------------------------------" << endl;
			dok << "Total\t\t\t\t\tRp." << harganya << endl;
			dok << "Uang\t\t\t\t\tRp." << uang << endl;
			dok << "Kembalian\t\t\t\tRp." << kembalian << endl;
			dok << "------------------------------------------------" << endl;
			dok << "--------------Terima Kasih----------------------" << endl;
			dok.close();

			cout << "\nKembalian : Rp." << kembalian << endl;

			return kembalian;
		}
		void cetakStruk(){
			string baris;
			ifstream struknya("Cetak.txt");

			cout << "\n\nCetak Struk...." << endl;

			system("PAUSE");

			while(getline(struknya, baris)){
				cout << baris << endl;
			}

			struknya.close();
		}

		void tambahData(){
			int cek, harga;

			string nama, bc;

			fstream data;
			data.open("Database.csv", ios::app);
				cout << "\n**************************************************************" << endl;
				cout << "**********************TAMBAH BARANG BARU********************" << endl;
				cout << "**************************************************************\n" << endl;
			do{
				do{
					cout << "\nMasukkan Kode Barang : ";
					cin >> bc;
					cek = cekAda(bc);
				}while(cek == 1);

				cout << "Masukkan Nama Barang : ";
				cin >> nama;

				cout << "Masukkan Harga : Rp. " ;
				cin >> harga;
				if(!bc.empty() && !nama.empty() && harga != 0){
					break;
				}
				cout << "Data Tidak Boleh Kosong";
			}while(bc.empty() && nama.empty() && harga == 0);

			data << bc << "," << nama << "," << harga << endl;

			data.close();
		}
};

int main(){
	int ftr, ttl;
	char ulang, tambahLagi;
	print cetak;
	Database harga;

	do{
		ftr = cetak.cetakAwal();

		if(ftr == 1){
			cetak.cekDatabase();
		}
		else if(ftr == 2){
			cetak.cekHarga();
		}
		else if(ftr == 3){
			ttl = cetak.programKasir();
			cetak.kembalian(ttl);
			cetak.cetakStruk();
			return 0;
		}
		else if(ftr == 4){
			do{
				cetak.tambahData();
				cout << "Apakah Anda Ingin Menambahkan Barang Lagi? (y/n)" << endl;
				cin >> tambahLagi;
			}while(tambahLagi == 'y' || tambahLagi == 'Y');
		}
		cout << "\n\n Tekan t Untuk Kembali / Tekan U Untuk Keluar" << endl;
		cin >> ulang;
	}while(ulang == 't' || ulang == 'u');


	return 0;
}
