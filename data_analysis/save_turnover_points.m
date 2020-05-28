function save_turnover_points(output_range, parent_dir, plate_position, ...
    plate_tol)
%SAVE_TURNOVER_POINTS Saves the turnover points into a text file

ds = turnover_points(output_range, parent_dir, plate_position, ...
    plate_tol);

output_matrix = zeros(length(output_range), 3);
output_matrix(:, 1) = output_range;
output_matrix(:, 2) = ds(:, 1);
output_matrix(:, 3) = ds(:, 2);

dlmwrite(sprintf('%s/cleaned_data/turnover_points.txt', parent_dir), ...
    output_matrix);
end