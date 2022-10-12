Vagrant.configure("2") do |config|
    config.vm.box = "ubuntu/jammy64"
    config.vm.hostname = "ubuntu"
    config.vm.provision "ansible_local" do |ansible|
        ansible.playbook = "ansible/playbook.yml"
        ansible.verbose = true
    end
        # Provider for VirtualBox
    config.vm.provider :virtualbox do |vb|
      vb.memory = "2048"
      vb.cpus = 2
    end
  # Provider for Docker
    config.vm.provider :docker do |docker, override|
      override.vm.box = nil
      docker.image = "welchsteven/vagrant-provider:ubuntu"
      docker.remains_running = true
      docker.has_ssh = true
      docker.privileged = true
      docker.volumes = ["/sys/fs/cgroup:/sys/fs/cgroup:rw"]
      docker.create_args = ["--cgroupns=host"]
    end
  end