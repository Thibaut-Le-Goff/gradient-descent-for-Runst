use rayon::prelude::*;

pub fn vec_vec(vector1: &[f32], vector2: &[f32]) -> Vec<f32> {
    let mut result: Vec<f32> = vec![0.0; vector1.len()];

    result.par_iter_mut().enumerate().for_each(|(iterator, value)| {
        *value = vector1[iterator] - vector2[iterator];

    });
    
    result
}
